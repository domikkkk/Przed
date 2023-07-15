#!/bin/env python3

# Dominik Sidorczuk
# Laboratorium PSI Zadanie 1
# 30.03.2023

import socket
import argparse
import time

BUFSIZE = 1024


def client(adres, port):

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            print(f"Sending messages to {adres}:{port}")
            for i in range(10):
                message = f"Message {i}".encode('utf-8')
                try:
                    s.sendto(message, (adres, port))
                except socket.error as e:
                    print("sendto error:", e)
                    exit(1)
                time.sleep(0.5)
    except socket.error as e:
        print("socket creation error:", e)
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog='klient_udp.py',
        description='Klient wysyłąjący 10 wiadomości do serwera',
        epilog='Przykład: python3 klient_udp.py 127.0.0.1 1234')
    parser.add_argument(
        'adres', type=str, help='adres serwera')
    parser.add_argument(
        'port', type=int, help='port do komunikacji')
    args = parser.parse_args()

    if 0 < args.port < 65536:
        client(args.adres, args.port)
    else:
        raise ValueError(f"Invalid port: {args.port}")
