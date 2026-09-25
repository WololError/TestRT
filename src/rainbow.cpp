#include "rainbow.hpp"
#include "sha256.h"
#include <cstdint>

const std::string ALPHABET = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
const int BASE = 62; // ALPHABET.size()

std::string R(const std::string& hash_hex, int column, int length) {
    // truncate the hash to its first 16 hex chars
    std::uint64_t value = std::stoull(hash_hex.substr(0, 16), nullptr, 16);

    // large odd constant: spreads the influence of column across all of value,
    // instead of only touching the last character of the password
    value += static_cast<std::uint64_t>(column) * 0x9E3779B97F4A7C15ULL;

    std::string password(length, ' ');
    for (int i = length - 1; i >= 0; i--) {
        password[i] = ALPHABET[value % BASE];
        value /= BASE;
    }
    return password;
}

std::string buildChain(const std::string& head, int chainLength, int passwordSize) {
    std::string password = head;
    for (int column = 0; column < chainLength; column++) {
        std::string hash = sha256(password);
        password = R(hash, column, passwordSize);
    }
    return password; // tail
}