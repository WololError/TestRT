#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "sha256.h"


std::string genPassword(int size) {

    std::string chars = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789";

    std::string password = "";

    for (int i = 0; i < size; i++) {
        password += chars[rand() % chars.size()];
    }

    return password;
}


int main() {
    srand(time(nullptr));

    std::string password = genPassword(10);

    std::string hash = sha256(password);

    std::cout << "MDP  : " << password << std::endl;
    std::cout << "SHA256 : " << hash << std::endl;
    return 0;
}
