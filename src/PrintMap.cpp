#include "PrintMap.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

void printCodeMap(const std::unordered_map<unsigned char, std::vector<bool>>& codeMap) {
    std::cout << "\nCharacter-to-bits mapping:\n";
    for (const auto& pair : codeMap) {
        unsigned char ch = pair.first;
        const auto& bits = pair.second;

        // Print character in readable form
        std::cout << "  ";
        if (std::isprint(ch)) {
            std::cout << "'" << ch << "'";
        } else {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)ch << std::dec;
        }

        std::cout << " : ";

        // Print bit sequence
        for (bool bit : bits) {
            std::cout << bit;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
