#include <iostream>
#include "gen_table.hpp"

int main() {

    int MIN = 2;
    int MAX = 5;

    for (int i = MIN ; i <= MAX; i++) {
        genRT(i, 1000, 1000);
        std::cout << "RT/RT_" << i <<".csv generated." << std::endl;
    }
    return 0;
}
