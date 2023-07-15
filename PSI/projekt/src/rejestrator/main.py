# 05 May, 2023
# Dominik Sidorczuk, Tomasz Sroka, Fedir Tsupin

import socket
import common
import argparse
import szyfrowanie
import keys
import json
import logging
import threading
import time
import retransmit


class Queue:
    lock = threading.Lock()
    is_empty = threading.Semaphore(0)
    queue = []


def retransmission_panic():
    logger = logging.getLogger(__name__)
    logger.error("Retransmission failed")
    exit(1)


def authenticate(s: socket, login, password) -> int:
    """
    Sends authentication info and returns key from response message, or None.
    Uses RSA
    """
    logger = logging.getLogger(__name__)
    data = login + "&" + password
    # hasło = mieszu mieszu hasło
    code = str(common.CODES.rejestrator_auth.value)
    # kod, zawartość
    data = code + data
    tx = szyfrowanie.encrypt_RSA(keys.pub_key, data.encode("utf-8"))

    tx = str(tx).encode("utf-8")
    response = retransmit.repeat_send(s, tx, retransmission_panic)

    code, response = int(response[:1].decode("utf-8")), response[1:]

    if code == common.CODES.auth_success.value:
        logger.debug("Received auth")
        return True
    elif code == common.CODES.auth_error.value:
        logger.error(f"Unable to authenticate: {response.decode('utf-8')}")
        return False
    else:
        logger.error("Unknown auth error")
        return False


def decrypt_rsa(data: str):
    rx = szyfrowanie.decrypt_RSA(keys.pub_key, data)
    return rx


def heartbeat_thread(s):
    logger = logging.getLogger(__name__)
    data = "beat"
    code = str(common.CODES.heartbeat.value)
    data = code + data
    heatbeat_message = str(
        szyfrowanie.encrypt_RSA(keys.pub_key, data.encode("utf-8"))
    ).encode("utf-8")
    while True:
        s.send(heatbeat_message)
        logger.debug("Heartbeat!")
        time.sleep(1)


def client(server_ip, port, login, password):
    logger = common.init_logger("rejestrator")
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # s.bind((HOST, PORT))  # opcjonalne przypisanie adresu i portu do klienta (domyślnie mamy 127.0.0.1, a port jakiś wolny), HOST i PORT niezdefiniowane
        s.connect((server_ip, port))
        if not authenticate(s, login, password):
            logger.error("Unable to authenticate!")
            exit(0)
        logger.debug("Authentication succeeded")

        t2 = threading.Thread(target=heartbeat_thread, args=([s]))
        t2.start()

        while True:
            # otrzymujemy odpowiedź od serwera
            data = s.recv(common.BUFSIZE).decode("utf-8")
            data = decrypt_rsa(int(data))
            if int(data[:1]) == common.CODES.sensor_data.value:
                data = json.loads(data[1:])
                logger.debug("Received data from brama")
                print(data)
            else:
                logger.info("Unknown message")

        close(s)

    except socket.error as e:
        logger.error("Socket error" + str(e))
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog="rejestrator.py",
        description="Odczytuje dane json",
        epilog="Przykład: python3 rejestrator.py 127.0.0.1 1234",
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
