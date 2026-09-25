#ifndef GEN_TABLE_HPP
#define GEN_TABLE_HPP

#include <string>

// Generates a random password of a given length.
std::string genPassword(int length);

// Generates a rainbow table for a given password length,
// and writes it to RT/RT_<passwordSize>.csv
void genRT(int passwordSize, int numberOfChains = 1000, int chainLength = 100);

#endif