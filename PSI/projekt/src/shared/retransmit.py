# 25 May, 2023
# Tomasz Sroka

import time
import socket
import common


def repeat_send(s, data: bytes, on_fail, repeat_count=10):
    s.setblocking(0)
    message = None
    for i in range(repeat_count):
        if message:
            s.setblocking(1)
            return message
        s.send(data)
        time.sleep(0.1)  # attempt to wait for the packet
        try:
            message = s.recv(common.BUFSIZE)
        except socket.error as e:
            time.sleep(0.5)
    s.setblocking(1)
    return on_fail()
