# 05 May, 2023
# Dominik Sidorczuk, Tomasz Sroka, Krzysztof Stawarski, Fedir Tsupin

from enum import Enum
import logging

SERVER_IP = "127.0.0.1"
BUFSIZE = 1024

# don't allow more to connect
MAX_SENSORS = 1024
MAX_RECORDERS = 32

heartbeat_interval = 1  # seconds


class CODES(Enum):
    sensor_auth = 0
    rejestrator_auth = 1
    auth_success = 2
    auth_error = 3
    sensor_data = 4
    heartbeat = 5
    sensor_required_tochange_aeskey = 6

# authorisation config
SALT_LENGTH = 16
DB_PATH = "./database.csv"
DELIMITER = ","
SEPARATOR = "&"

# log config
LOG_DIR = "./log/"

# symmetric encryption config
AES_CHANGE_INTERVAL = 10
AES_CHANGE_IGNORE_LIMIT = 20  # after 20 messages unauthenticate


def init_logger(device_name="default", outfile=None):
    """
    device_name: used for log file
    """

    if outfile is None:
        outfile = device_name + ".log"
    logger = logging.getLogger(device_name)
    logger.setLevel(logging.DEBUG)

    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)

    fh = logging.FileHandler(LOG_DIR + outfile, encoding="utf-8")
    fh.setLevel(logging.DEBUG)

    c_formatter = logging.Formatter("%(levelname)s - %(message)s")
    f_formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")

    ch.setFormatter(c_formatter)
    fh.setFormatter(f_formatter)

    logger.addHandler(ch)
    logger.addHandler(fh)

    return logger
