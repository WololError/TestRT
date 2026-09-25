#include "gen_table.hpp"
#include "rainbow.hpp"
#include <fstream>
#include <random>
#include <stdexcept>

std::string genPassword(int length) {

    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> dist(0, BASE - 1);

    std::string password;
    for (int i = 0; i < length; i++)
        password += ALPHABET[dist(rng)];
    return password;
}

void genRT(int passwordSize, int numberOfChains, int chainLength) {

    std::string filename = "RT/RT_" + std::to_string(passwordSize) + ".csv";
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open " + filename);

    file << passwordSize << "\n";

    for (int i = 0; i < numberOfChains; i++) {
        std::string head = genPassword(passwordSize);
        std::string tail = buildChain(head, chainLength, passwordSize);
        file << head << "," << tail << "\n";
    }
}