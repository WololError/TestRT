import csv
import hashlib
import os
import secrets
import string

ALPHABET = string.ascii_letters + string.digits
MIN_LEN = 6
MAX_LEN = 10
LEN_RANGE = MAX_LEN - MIN_LEN + 1


def generate_password() -> str:
    """Generate a password of random length."""
    length = secrets.randbelow(LEN_RANGE) + MIN_LEN
    return ''.join(secrets.choice(ALPHABET) for _ in range(length))


def H(password: str) -> str:
    """SHA-256 hash of a password."""
    return hashlib.sha256(password.encode()).hexdigest()


def R(hash_value: str, column: int) -> str:
    """Reduce a hash to a password."""
    base = len(ALPHABET)
    value = int(hash_value, 16) + column

    length = MIN_LEN + (value % LEN_RANGE)
    value //= LEN_RANGE
    value %= base ** length

    password = ""
    for _ in range(length):
        password = ALPHABET[value % base] + password
        value //= base

    return password


def build_chain(head: str, chain_length: int) -> str:
    """Build a chain and return its tail."""
    password = head
    for column in range(chain_length):
        password = R(H(password), column)
    return password


if __name__ == "__main__":
    number_of_chains = 100
    chain_length = 100

    os.makedirs("data", exist_ok=True)
    with open("data/RT.csv", "w", newline="") as file:
        writer = csv.writer(file)
        for _ in range(number_of_chains):
            head = generate_password()
            tail = build_chain(head, chain_length)
            writer.writerow([head, tail])