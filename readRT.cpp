#include <iostream>

#include "SimpleCrack.hpp"
#include "rainbow.hpp"
#include "gen_table.hpp"
#include "sha256.h"

int main() {
    RainbowTable table = readTable("RT/RT_4.csv");
    std::cout << table.chains.size() << " chaines chargees, longueur mdp = " << table.passwordSize << ", longueur chaine = " << table.chainLength << std::endl;

    std::string targetPassword = genPassword(table.passwordSize);
    std::string targetHash = sha256(targetPassword);

    std::cout << "mot de passe cache : " << targetPassword << std::endl;
    std::cout << "hash a casser      : " << targetHash << std::endl;

    std::string result = crackHash(targetHash, table);

    if (!result.empty())
        std::cout << "mot de passe retrouve : " << result << std::endl;
    else
        std::cout << "mot de passe NON retrouve (?)" << std::endl;

    return 0;
}