#ifndef RAINBOW_HPP
#define RAINBOW_HPP

#include <string>

extern const std::string ALPHABET;
extern const int BASE;

// Reduces a hash to a password of a given length, depending on the column.
std::string R(const std::string& hash_hex, int column, int length);

// Builds a full chain starting from a head, returns the tail.
std::string buildChain(const std::string& head, int chainLength, int passwordSize);

#endif