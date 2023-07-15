#!/bin/env python3

# Dominik Sidorczuk
# Laboratorium PSI Zadanie 1
# 30.03.2023

import socket
import argparse


HOST = 'localhost'
BUFSIZE = 1024


def server(port=0):

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            result = s.bind((HOST, port))
            if result == -1:
                print(f"Bind error")
                exit(1)
            port = s.getsockname()[1]
            print(f"UDP server.py's listening on port {port}")
            while True:
                try:
                    data, address = s.recvfrom(BUFSIZE)
                except socket.error as e:
                    print("recvfrom error:", e)
                    exit(1)
                print(f"received.py {data.decode('utf-8')} from {address}")
    except socket.error as e:
        print("socket creation error:", e)
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog='serwer_udp.py',
        description='Serwer czytający struktury C',
        epilog='Przykład: python3 serwer_udp.py [port]')
    parser.add_argument(
        'port', type=int, help='port serwera', default=0, nargs='?')
    args = parser.parse_args()

    if 0 <= args.port < 65536:
        server(args.port)
    else:
        raise ValueError(f"Invalid port: {args.port}")
