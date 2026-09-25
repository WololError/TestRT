#include "SimpleCrack.hpp"
#include "rainbow.hpp"
#include "sha256.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::unordered_map<std::string, std::string> readTable(const std::string& filename, int& passwordSize, int& chainLength) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open " + filename);

    std::string firstLine;
    std::getline(file, firstLine);
    std::stringstream header(firstLine);
    std::string psStr, clStr;
    std::getline(header, psStr, ',');
    std::getline(header, clStr, ',');
    passwordSize = std::stoi(psStr);
    chainLength = std::stoi(clStr);

    std::unordered_map<std::string, std::string> table;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string head, tail;
        std::getline(ss, head, ',');
        std::getline(ss, tail, ',');
        table[tail] = head; // tail -> head
    }
    return table;
}


std::string crackHash(const std::string& targetHash, const std::unordered_map<std::string, std::string>& table, int passwordSize, int chainLength) {

    for (int j = chainLength - 1; j >= 0; j--) {
        // replay from column j to the end, as if targetHash was the hash at column j
        std::string candidate = R(targetHash, j, passwordSize);
        for (int col = j + 1; col < chainLength; col++)
            candidate = R(sha256(candidate), col, passwordSize);

        // O(1) average lookup instead of scanning the whole table
        auto it = table.find(candidate);

        if (it != table.end()) {
            // matching tail found -> replay from the REAL head to verify
            // and find the actual password (avoids false alarms)
            std::string replay = it->second;
            for (int col = 0; col < chainLength; col++) {
                if (sha256(replay) == targetHash)
                    return replay;
                replay = R(sha256(replay), col, passwordSize);
            }
        }
    }
    return ""; // not cracked
}