#!/bin/env python3

# Krzysztof Stawarski
# Laboratorium PSI Zadanie 1
# 30.03.2023

import socket
import struct
import struct_parser
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
                    bindata, addr = s.recvfrom(BUFSIZE)
                    struct_C_format, addr = s.recvfrom(BUFSIZE)
                except Exception as e:
                    print("recvfrom error", e)
                    exit(1)
                struct_C_format = struct_C_format.decode('ascii')

                try:
                    struct_python_format, names = struct_parser.parse_struct(
                        struct_C_format)
                except struct_parser.InvalidFieldTypeException as e:
                    raise e  # pass higher
                except Exception:
                    raise ValueError("Malformed struct")
                    exit(1)

                joined_tuples = ["".join(x) for x in struct_python_format]

                # '!' -> network alignment (big endian)
                struct_fmt = "!" + "".join(joined_tuples)
                unpacked = struct.unpack(struct_fmt, bindata)

                result = {}

                pos = 0
                for type, name in zip(struct_python_format, names):
                    if isinstance(type, tuple):
                        # collect next n elements into array
                        count = int(type[0])
                        arr = unpacked[pos:pos+count]
                        if type[1] == 'c':
                            # char array is assumed to be a proper string
                            arr = b''.join(arr).decode('ascii').strip('\0')
                        result[name] = arr
                        pos += count
                    else:
                        result[name] = unpacked[pos]
                        pos += 1

                print(repr(result))
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
