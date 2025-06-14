#include "PrintMap.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

// Prints the symbol-to-code mapping in a human-readable format.
// Printable characters are shown directly; non-printables in hex.
// Bit sequences are printed as 0s and 1s.
void printCodeMap(const std::unordered_map<unsigned char, std::vector<bool>>& codeMap) {
    std::cout << "\nCharacter-to-bits mapping:\n";
    for (const auto& pair : codeMap) {
        unsigned char ch = pair.first;
        const auto& bits = pair.second;

        // Print the character or its hex representation
        std::cout << "  ";
        if (std::isprint(ch)) {
            std::cout << "'" << ch << "'";
        } else {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)ch << std::dec;
        }

        std::cout << " : ";

        // Print the corresponding bit sequence
        for (bool bit : bits) {
            std::cout << bit;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
