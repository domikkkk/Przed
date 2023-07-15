SERVER_IP = '127.0.0.1'
CLIENT_IP = '127.0.0.2'
CLIENT_PORT = 1026
MAX_BUFSIZE = 32
HEADER_LEN = 4


def convert_int_to_char(ln):
    ln = str(ln)
    ln = (HEADER_LEN-len(ln)) * '0' + ln
    return ''.join(chr(ord(i) - 48) for i in ln)

# można jeszcze jakieś stałe dodać...
