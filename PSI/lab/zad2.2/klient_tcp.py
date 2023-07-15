#!/bin/env python3

# Dominik Sidorczuk
# Laboratorium PSI Zadanie 2.2
# 15.04.2023


import socket
import common
import argparse


def client(server_ip, port):
    message = 'Hello my friend! ' + 150 * '1'
    header = len(message)
    message = common.convert_int_to_char(header) + message
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            # s.bind((common.CLIENT_IP, common.CLIENT_PORT))  # opcjonalne przypisanie adresu i portu do klienta (domyślnie mamy 127.0.0.1, a port jakiś wolny), HOST i PORT niezdefiniowane
            s.connect((server_ip, port))
            try:
                s.send(message.encode('utf-8'))  # wysyłamy do serwera
            except TypeError:  # gdyby w sendall() dać jakąś zmienną to wtedy to sprawdzanie ma sens czy się zakodowało tekst, bo na razie są dane binarne
                print("Wrong data type")
                s.close()
                exit(1)
            data = s.recv(common.MAX_BUFSIZE)  # otrzymujemy odpowiedź od serwera
        print('Server:', data.decode('utf-8'))
        s.close()
    except socket.error as e:
        print("Socket error", e)
        exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        prog='klient_tcp.py',
        description='Klient wysyłąjący wiadomość do serwera',
        epilog='Przykład: python3 klient_tcp.py 127.0.0.1 1234')
    parser.add_argument(
        'adres', type=str, help='adres serwera')
    parser.add_argument(
        'port', type=int, help='port do komunikacji')
    args = parser.parse_args()

    if 0 < args.port < 65536:
        client(args.adres, args.port)
    else:
        raise ValueError(f"Invalid port: {args.port}")
