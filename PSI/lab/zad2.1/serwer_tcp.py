#!/bin/env python3

# Dominik Sidorczuk
# Laboratorium PSI Zadanie 2.1
# 15.04.2023


import socket
import common
import argparse


def server(port):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.bind((common.SERVER_IP, port)) == -1:
                print("Bind error")
                exit(1)
            port = s.getsockname()[1]  # w razie gdyby było 0 to port jest jakoś przydzielany, więc wypada wiedzieć na jakim porcie serwer nasłuchuje
            print("TCP server.py's listening on port {}".format(port))
            s.listen(5)  # ilość nieodebranych połączeń jakie może nawiązać jeszcze
            while True:  # tutaj można dodać jakiś sensowny warunek do kiedy ma pracować, ale chyba nie trzeba
                conn, addr = s.accept()  # akceptujemy połącznie klienta, któregoś... chyba kto pierwszy ten lepszy

                with conn:
                    print("Connect from: {}:{}".format(addr[0], addr[1]))   # w client_tcp.py można by bind-em przypisać mu sztucznie jakiś adres i port wtedy będzie widać różnicę, bo tak to będzie 127.0.0.1:losowy port
                    while True:
                        data = conn.recv(common.BUFSIZE)
                        if not data:
                            break
                        try:
                            conn.sendall(b"Data received!")  # wysyłamy odpowiedź, że otrzymaliśmy dane
                        except TypeError:  # gdyby w sendall() dać jakąś zmienną to wtedy to sprawdzanie ma sens czy się zakodowało tekst
                            conn.close()
                            print("Wrong data type. Connection closed")
                            exit(1)
                        print("Receiving data #", data.decode('utf-8'))
            conn.close()
            print("Connection closed")

    except socket.error as e:
        print("Socket error", e)
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog='serwer_tcp.py',
        description='Serwer TCP',
        epilog='Przykład: python3 serwer_tcp.py [port]')
    parser.add_argument(
        'port', type=int, help='port serwera', default=0, nargs='?')
    args = parser.parse_args()

    if 0 <= args.port < 65536:
        server(args.port)
    else:
        raise ValueError(f"Invalid port: {args.port}")
