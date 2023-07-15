# 05 May, 2023
# Dominik Sidorczuk

import random
import base64
from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes
from Cryptodome.Util.number import getPrime


HEX_LEN_KEY = 4
HEX_LEN_FI = 2
KEY_LEN = 16


def hexx(a: int) -> str:
    a = hex(a)[2:]
    if len(a) % 2 != 0:
        a = '0' + a
    return a


def fact_key(a: str, b: int) -> 'tuple[str, int]':
    q = int(a[:b], 16)
    return a[b:], q


def encode_key(n: int, d: int) -> str:
    hex_n, hex_d = hexx(n), hexx(d)
    key = hexx(len(str(hex_n))//2) + hex_n + hexx(len(str(hex_d))//2) + hex_d
    hex_len = hexx(len(key)//2)
    if len(hex_len) < HEX_LEN_KEY:
        hex_len = '0' * (HEX_LEN_KEY - len(hex_len)) + hex_len
    key = hex_len + key
    return base64.b64encode(key.encode('utf-8')).decode('utf-8')


def decode_key(key: str) -> 'tuple[int, int]':
    key = base64.b64decode(key.encode('utf-8')).decode('utf-8')
    key, lenght = fact_key(key, HEX_LEN_KEY)
    if lenght*2 != len(key):
        raise ValueError
    key, len_n = fact_key(key, HEX_LEN_FI)
    key, n = fact_key(key, len_n*2)
    key, len_d = fact_key(key, HEX_LEN_FI)
    _, d = fact_key(key, len_d*2)
    return n, d


def NWD(a: int, b: int) -> int:
    if b == 0:
        return a
    return NWD(b, a % b)


def RSA_keys() -> 'tuple[str, str]':
    p = getPrime(512)
    q = getPrime(512)
    phi = (p-1)*(q-1)
    n = p * q
    e, d = 3, 0
    while NWD(e, phi) != 1:
        e = random.randrange(3, phi, 2)
        # e += 2
    d = odwr_mod(e, phi)
    return encode_key(n, d), encode_key(n, e)


def odwr_mod(a: int, n: int) -> int:
    a0, n0 = a, n
    p0, p1 = 0, 1
    q, r = n0//a0, n0 % a0
    while r > 0:
        t = p0 - p1*q
        if t >= 0:
            t = t % n
        else:
            t = n - ((-t) % n)
        p0, p1 = p1, t
        n0, a0 = a0, r
        q, r = n0//a0, n0 % a0
    return p1


def pot_mod(key: str, t: int) -> int:
    n, e = decode_key(key)
    e0, c = e, 1
    while e0 > 0:
        if e0 % 2:
            c = (t * c) % n
        t = (t * t) % n
        e0 //= 2
    return c % n


def encrypt_RSA(key: str, mes: str) -> int:
    """
    Szyfrowanie asymetryczne RSA
    Args:
        key (str): klucz publiczny lub prywatny
        mes (str): wiadomość

    Returns:
        int: zaszyfrowany int
    """
    a = int.from_bytes(mes, 'big')
    return pot_mod(key, a)


def decrypt_RSA(key: str, t: int) -> str:
    """
    Odszyfrowanie asymetryczne RSA
    Args:
        key (str): klucz publiczny lub prywatny
        length (int): długość z inta na ile bajtów chcemy odtworzyć
        t (int): zaszyfrowana wartość (duży int)

    Returns:
        str: Ciąg znaków odszyfrowany
    """
    b = pot_mod(key, t)
    length = len(bin(b))//8
    return b.to_bytes(length, 'big')


def get_random_key_aes() -> bytes:
    """
    Returns:
        str: Klucz do szyfrowania symetrycznego AES
    """
    return get_random_bytes(KEY_LEN)


def encrypt_AES(message: str, key: str) -> str:
    """
    Szyfrowanie symetryczne AES
    Args:
        message (str): wiadomość do zaszyfrowania
        key (str): klucz

    Returns:
        str: zaszyfrowany ciąg znaków
    """
    cipher = AES.new(key, AES.MODE_EAX)
    ciphertext, tag = cipher.encrypt_and_digest(message)
    return cipher.nonce + ciphertext + tag


def decrypt_AES(message: str, key: str) -> str:
    """
    Odszyfrowywanie wiadomości AES
    Args:
        message (str): zaszyfrowana wiadomość
        key (str): klucz

    Returns:
        str: Odszyfrowana wiadomość
    """
    nonce = message[:16]
    ciphertext = message[16:-16]
    tag = message[-16:]
    cipher = AES.new(key, AES.MODE_EAX, nonce)
    plaintext = cipher.decrypt_and_verify(ciphertext, tag)
    return plaintext
