#include <iostream>
#include "gen_table.hpp"

int main() {
    for (int i = 2 ; i <= 4; i++) {
        genRT(i, 1000, 100);
        std::cout << "RT/RT_" << i <<".csv generated." << std::endl;
    }
    return 0;
}
