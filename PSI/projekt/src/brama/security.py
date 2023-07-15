# 05 May, 2023
# Fedir Tsupin

import csv
import secrets
import hashlib
import secrets
import common


def read_from_csv(login):
    csv_file = csv.reader(open(common.DB_PATH, "r"))
    for row in csv_file:
        if row[0] == login:
            return row
    return None


def write_to_csv(row):
    with open(common.DB_PATH, "w") as csvfile:
        writer = csv.writer(csvfile, delimiter=common.DELIMITER)
        writer.writerow(row)


def add_user(login, password):
    salt_hex = generate_salt()
    hashed_password = hash(password, salt_hex)
    write_to_csv([login, str(hashed_password), str(salt_hex)])


def hash(password, salt_hex):
    salt = bytes.fromhex(salt_hex)
    data = password.encode("utf-8") + salt
    hash_object = hashlib.sha256()
    hash_object.update(data)
    hash_hex = hash_object.hexdigest()
    return hash_hex


def generate_salt(length=common.SALT_LENGTH):
    salt = secrets.token_bytes(length)
    salt_hex = salt.hex()
    return salt_hex


def authorize(data):
    login, password = data.split(common.SEPARATOR)
    row = read_from_csv(login)
    if row is None:
        return False
    login, hash_hex, salt = row
    return hash_hex == hash(password, salt)
