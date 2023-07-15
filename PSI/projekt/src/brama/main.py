# 05 May, 2023
# Dominik Sidorczuk, Tomasz Sroka, Fedir Tsupin

import socket
import common
import argparse
import security
import szyfrowanie
import keys
import cbor2
import json
import threading
import time


class Gateway:
    def __init__(self, port):
        # AES is used instead of RSA
        # ip addresses of those who are authenticated
        self.connected_sensors = set([])
        self.AES_keys = {}
        # here RSA always
        self.connected_recorders = set([])
        # heartbeat timers
        self.timers = {}
        self.counter = {}
        self.logger = common.init_logger("brama")
        self.socket = self.init_socket(port)

        self.hearbeat_margin = 5  # how many drops to tolerate

    def reset_timer(self, callback, who, interval=None):
        """
        Resets timer for client. If timer wasn't running, it is created.
        callback is a function that will be fired when timer reaches 0.
        The function receives `who` as argument too.
        Default interval is 5 times the heartbeat
        """
        if interval is None:
            interval = common.heartbeat_interval * self.hearbeat_margin
        if who in self.timers:
            # cancel if it was already running
            self.timers[who].cancel()

        self.timers[who] = threading.Timer(interval, function=callback, args=([who]))
        self.timers[who].start()

    def init_socket(self, port) -> socket:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            if s.bind((common.SERVER_IP, port)) == -1:
                self.logger.error("Bind error")
                exit(1)
            port = s.getsockname()[1]
            self.logger.info("UDP brama.py's listening on port {}".format(port))
        except socket.error as e:
            self.logger.error("Socket error: " + str(e))
            exit(1)
        return s

    # @TODO: send a disconnect message!!!
    # right now when device happens to wake up,
    # it will keep spamming as unauthorised
    def disconnect_sensor(self, who):
        self.connected_sensors.remove(who)
        self.timers[who].cancel()
        del self.timers[who]
        self.logger.info(f"Sensor timeout: {who}")

    def disconnect_recorder(self, who):
        self.connected_recorders.remove(who)
        self.timers[who].cancel()
        del self.timers[who]
        self.logger.info(f"Recorder timeout: {who}")

    def connect_sensor(self, who: tuple, key: bytes) -> str:
        """
        Returns AES key as well
        """
        self.connected_sensors.add(who)
        self.AES_keys[who] = key

        # setup timer
        self.reset_timer(self.disconnect_sensor, who)

    def connect_recorder(self, who: tuple) -> str:
        self.connected_recorders.add(who)
        # setup timer
        self.reset_timer(self.disconnect_recorder, who)

    def send_to_recorders(self, data: bytes):
        for reg in self.connected_recorders:
            self.socket.sendto(data, reg)

    def send_to_sensor_to_change_key(self, who: tuple):
        code = str(common.CODES.sensor_required_tochange_aeskey.value).encode("utf-8")
        self.socket.sendto(code, who)

    def is_sensor_connected(self, who: tuple):
        return who in self.connected_sensors

    def is_recorder_connected(self, who: tuple):
        return who in self.connected_recorders

    def is_connected(self, who: tuple):
        return self.is_recorder_connected(who) or self.is_sensor_connected(who)

    def try_authorise(self, data, address):
        # unknown address sent a message
        # assume this is RSA and that somebody wants to authenticate
        code_error = str(common.CODES.auth_error.value).encode("utf-8")
        try:
            data = szyfrowanie.decrypt_RSA(keys.priv_key, int(data))
            code, data = int(chr(data[0])), data[1:]
        except Exception:
            return code_error + b"Wrong RSA key"

        code_success = str(common.CODES.auth_success.value).encode("utf-8")
        # @TODO: Respond in RSA
        if common.CODES.sensor_auth.value == code:
            if len(self.connected_sensors) >= common.MAX_SENSORS:
                return code_error + b"Too many sensors! Try again later"
            creds, key_AES = data[:-17].decode("utf-8"), data[-16:]
            if security.authorize(creds):
                self.connect_sensor(address, key_AES)
                self.logger.info(f"New sensor connection from {address}")
                return code_success + b"Auth success"
            else:
                self.logger.info(f"Couldn't authorize sensor from {address}")
                return code_error + b"Invalid login and password"
        elif common.CODES.rejestrator_auth.value == code:
            if len(self.connected_recorders) >= common.MAX_RECORDERS:
                return code_error + b"Too many recorders! Try again later"
            creds = data.decode("utf-8")
            if security.authorize(creds):
                self.connect_recorder(address)
                self.logger.info(f"New recorder connection from {address}")
                return code_success + b"Auth success"
            else:
                self.logger.info(f"Couldn't authorize recorder from {address}")
                return code_error + b"Invalid login and password"
        else:
            return code_error + b"Unrecognised message (expected auth)"

    def loop(self):
        while True:
            try:
                data, address = self.socket.recvfrom(common.BUFSIZE)
            except socket.error as e:
                self.logger.error("recvfrom error:" + str(e))
                exit(1)
            send_this = self.handle_message(data, address)
            if send_this is not None:
                self.socket.sendto(send_this, address)

    def handle_message(self, data, address) -> bytes:
        """
        Do something with the message, return response to send or None.
        """
        if self.is_sensor_connected(address):
            # sensors always communicate on AES
            try:
                decrypted = szyfrowanie.decrypt_AES(data, self.AES_keys[address])
            except Exception:
                self.logger.info("Invalid data received or AES key")
                return None
            code, data = int(decrypted[:1].decode("utf-8")), decrypted[1:]
            self.logger.debug(f"Message ({code}): {data}")
            if common.CODES.sensor_data.value == code:
                # decrypt aes
                python_object = cbor2.loads(data)
                python_object["timestamp"] = int(time.time())
                jsonstr = json.dumps(python_object)
                jsonstr = str(common.CODES.sensor_data.value) + jsonstr
                encrypted = szyfrowanie.encrypt_RSA(
                    keys.priv_key, jsonstr.encode("utf-8")
                )
                tx = str(encrypted).encode("utf-8")
                self.logger.debug(f"Received sensor data from {address}")
                if address not in self.counter:
                    self.counter[address] = 0
                self.counter[address] += 1
                if self.counter[address] >= common.AES_CHANGE_INTERVAL:
                    self.send_to_sensor_to_change_key(address)
                    self.logger.info(f"change key! {address}")
                    if self.counter[address] >= common.AES_CHANGE_IGNORE_LIMIT:
                        self.logger.warn(f"sensor didnt respect limit! {address}")
                        self.disconnect_sensor(address)
                        return None
                self.send_to_recorders(tx)
                return None

            elif common.CODES.heartbeat.value == code:
                self.logger.debug(f"sensor heartbeat: {address}")
                self.reset_timer(self.disconnect_sensor, address)

            elif common.CODES.sensor_required_tochange_aeskey.value == code:
                self.AES_keys[address] = data
                self.counter[address] = 0

            else:
                self.logger.warn(f"Unknown sensor message from {address}")

        elif self.is_recorder_connected(address):
            data = int(data.decode("utf-8"))
            try:
                decrypted = szyfrowanie.decrypt_RSA(keys.priv_key, data)
            except Exception:
                self.logger.debug("Invalid data from unauthorised peer")
            code, data = int(decrypted[:1].decode("utf-8")), decrypted[1:]

            if common.CODES.heartbeat.value == code:
                self.logger.debug(f"registrator heartbeat: {address}")
                self.reset_timer(self.disconnect_recorder, address)

            else:
                self.logger.warn(f"Unknown recorder message from {address}")
        else:
            return self.try_authorise(data, address)


def server(port):
    gateway = Gateway(port)
    gateway.loop()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog="brama.py",
        description="Brama CBOR<->JSON",
        epilog="Przykład: python3 brama.py [port]",
    )
    parser.add_argument("port", type=int, help="port serwera", default=0, nargs="?")
    args = parser.parse_args()

    if 0 <= args.port < 65536:
        server(args.port)
    else:
        raise ValueError(f"Invalid port: {args.port}")
