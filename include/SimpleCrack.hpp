#ifndef SIMPLE_CRACK_HPP
#define SIMPLE_CRACK_HPP

#include <string>
#include <unordered_map>

struct RainbowTable {
    std::unordered_map<std::string, std::string> chains; // tail -> head
    int passwordSize;
    int chainLength;
};

// Reads a RT_<L>.csv file: first line is "passwordSize,chainLength",
// then head,tail pairs.
RainbowTable readTable(const std::string& filename);

// Tries to crack targetHash using the table. Returns "" if not found.
std::string crackHash(const std::string& targetHash, const RainbowTable& table);

#endif