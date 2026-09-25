#include "SimpleCrack.hpp"
#include "rainbow.hpp"
#include "sha256.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

RainbowTable readTable(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open " + filename);

    RainbowTable table;

    std::string firstLine;
    std::getline(file, firstLine);
    std::stringstream header(firstLine);
    std::string psStr, clStr;
    std::getline(header, psStr, ',');
    std::getline(header, clStr, ',');
    table.passwordSize = std::stoi(psStr);
    table.chainLength = std::stoi(clStr);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string head, tail;
        std::getline(ss, head, ',');
        std::getline(ss, tail, ',');
        table.chains[tail] = head; // tail -> head
    }
    return table;
}

std::string crackHash(const std::string& targetHash, const RainbowTable& table) {
    for (int j = table.chainLength - 1; j >= 0; j--) {
        // replay from column j to the end, as if targetHash was the hash at column j
        std::string candidate = R(targetHash, j, table.passwordSize);
        for (int col = j + 1; col < table.chainLength; col++)
            candidate = R(sha256(candidate), col, table.passwordSize);

        // O(1) average lookup instead of scanning the whole table
        auto it = table.chains.find(candidate);
        if (it != table.chains.end()) {
            // matching tail found -> replay from the REAL head to verify
            // and find the actual password (avoids false alarms)
            std::string replay = it->second;
            for (int col = 0; col < table.chainLength; col++)
            {
                if (sha256(replay) == targetHash)
                    return replay;
                replay = R(sha256(replay), col, table.passwordSize);
            }
        }
    }
    return ""; // not cracked
}