#include <iostream>

#include "SimpleCrack.hpp"
#include "rainbow.hpp"
#include "gen_table.hpp"
#include "sha256.h"

int main() {

    int passwordSize, chainLength;
    std::unordered_map<std::string, std::string> table = readTable("RT/RT_4.csv", passwordSize, chainLength);
    std::cout << table.size() << " chaines chargees, longueur mdp = " << passwordSize
               << ", longueur chaine = " << chainLength << std::endl;

    std::string targetPassword = genPassword(passwordSize);
    std::string targetHash = sha256(targetPassword);

    std::cout << "mot de passe cache : " << targetPassword << std::endl;
    std::cout << "hash a casser      : " << targetHash << std::endl;

    std::string result = crackHash(targetHash, table, passwordSize, chainLength);

    if (!result.empty())
        std::cout << "mot de passe retrouve : " << result << std::endl;
    else
        std::cout << "mot de passe NON retrouve (?)" << std::endl;

    return 0;
}