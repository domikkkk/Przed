# 05 May, 2023
# Tomasz Sroka, Dominik Sidorczuk, Fedir Tsupin

import socket
import common
import argparse
import szyfrowanie
import keys
import cbor2
import time
import random
import threading
import logging
import retransmit


class Connection:
    key_AES = None


class Queue:
    lock = threading.Lock()
    is_empty = threading.Semaphore(0)
    queue = []


def collect_data(id_sensora: str):
    """
    Symulacja zbierania danych
    """
    data = {
        "id_sensora": id_sensora,  # @TODO: get identifier from login somehow
        "dane": {
            "temperatura": random.randint(10, 30),
        },
    }
    return data


def prepare_data(data: bytes, key):
    """
    collected data is encrypted with aes and packed into a `communication` type message
    """
    data = cbor2.dumps(data)
    code = common.CODES.sensor_data.value
    data = str(code).encode("utf-8") + data
    # kod, długość wiadomości, wiadomość cbor
    tx = szyfrowanie.encrypt_AES(data, key)
    return tx


def retransmission_panic():
    logger = logging.getLogger(__name__)
    logger.error("Retransmission failed")
    exit(1)


def authenticate(s, login: str, password: str) -> int:
    """
    Sends authentication info and returns key from response message, or None.
    Uses RSA
    """
    logger = logging.getLogger(__name__)
    # create auth message
    data = login + "&" + password
    # adding AES key
    key_AES = szyfrowanie.get_random_key_aes()
    logger.debug(f"New key generated: {key_AES}")
    # mieszu mieszu
    data = data.encode("utf-8") + b"#" + key_AES
    code = str(common.CODES.sensor_auth.value).encode("utf-8")
    # mieszu mieszu
    data = code + data
    tx = szyfrowanie.encrypt_RSA(keys.pub_key, data)

    tx = str(tx).encode("utf-8")
    # wait for response, it can be either success or failure
    response = retransmit.repeat_send(s, tx, retransmission_panic)

    code = int(response[:1].decode("utf-8"))

    if code == common.CODES.auth_success.value:
        logger.debug("Received auth")
        return key_AES
    elif code == common.CODES.auth_error.value:
        # it only makes sense to decode when it's not a key
        logger.error(f"Unable to authenticate: {key_AES}")
        return None
    else:
        logger.error("Unknown auth error")
        return None


def heartbeat_thread():
    logger = common.init_logger("sensor")
    data = "beat"
    code = str(common.CODES.heartbeat.value)
    data = code + data
    while True:
        heatbeat_message = szyfrowanie.encrypt_AES(
            data.encode("utf-8"), Connection.key_AES
        )
        with Queue.lock:
            Queue.queue.append(heatbeat_message)
            Queue.is_empty.release(1)
            logger.debug("Heartbeat!")
        time.sleep(1)


def data_thread(login):
    logger = logging.getLogger(__name__)
    while True:
        data = prepare_data(collect_data(login), Connection.key_AES)
        with Queue.lock:
            Queue.queue.append(data)
            Queue.is_empty.release(1)
            logger.debug("Sensor produced data")
        time.sleep(2)


def change_key_thread(s):
    logger = logging.getLogger(__name__)
    while True:
        data = s.recv(common.BUFSIZE)
        if (
            int(data.decode("utf-8"))
            != common.CODES.sensor_required_tochange_aeskey.value
        ):
            logger.error("incorrect code")
            continue
        new_key = szyfrowanie.get_random_key_aes()
        logger.debug(f"New key generated: {new_key}")
        code = str(common.CODES.sensor_required_tochange_aeskey.value).encode("utf-8")
        mess = code + new_key
        data = szyfrowanie.encrypt_AES(mess, Connection.key_AES)
        Connection.key_AES = new_key
        with Queue.lock:
            Queue.queue.append(data)
            Queue.is_empty.release(1)
            logger.info("Generated new AES_key")
        time.sleep(0.5)


def client(server_ip, port, login, password):
    i = 0
    logger = common.init_logger(__name__, outfile="sensor.log")
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            # s.bind((HOST, PORT))  # opcjonalne przypisanie adresu i portu do klienta (domyślnie mamy 127.0.0.1, a port jakiś wolny), HOST i PORT niezdefiniowane
            logger.info("Trying to connect...")
            s.connect((server_ip, port))
            logger.info("Authenticating...")
            Connection.key_AES = authenticate(s, login, password)
            if Connection.key_AES is None:
                exit(0)
            logger.info("Authenticated")
            t1 = threading.Thread(target=data_thread, args=([login]))
            t2 = threading.Thread(target=heartbeat_thread)
            t3 = threading.Thread(target=change_key_thread, args=([s]))
            t1.start()
            t2.start()
            t3.start()
            logger.debug("Started threads")
            # implement logging here
            while Queue.is_empty.acquire():
                with Queue.lock:
                    s.send(Queue.queue.pop())
                    logger.debug(f"Sent data to brama {i}")
                    i += 1
    except socket.error as e:
        logger.error("Socket error: " + str(e))
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog="sensor.py",
        description="Klient wysyłąjący wiadomość do serwera",
        epilog="Przykład: python3 sensor.py 127.0.0.1 1234",
    )
    parser.add_argument("adres", type=str, help="adres serwera")
    parser.add_argument("port", type=int, help="port do komunikacji")
    parser.add_argument("login", type=str, help="login")
    parser.add_argument("password", type=str, help="hasło")
    args = parser.parse_args()

    if 0 < args.port < 65536:
        client(args.adres, args.port, args.login, args.password)
    else:
        raise ValueError(f"Invalid port: {args.port}")
