#ifndef SIMPLE_CRACK_HPP
#define SIMPLE_CRACK_HPP

#include <string>
#include <unordered_map>

// Reads a RT_<L>.csv file: first line is "passwordSize,chainLength",
// then head,tail pairs. Returns a map tail -> head for O(1) average lookup.
std::unordered_map<std::string, std::string> readTable(const std::string& filename, int& passwordSize, int& chainLength);

// Tries to crack targetHash using the table. Returns "" if not found.
std::string crackHash(const std::string& targetHash, const std::unordered_map<std::string, std::string>& table, int passwordSize, int chainLength);

#endif