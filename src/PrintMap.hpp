#pragma once
#include <unordered_map>
#include <vector>

// Prints the symbol-to-code mapping (Huffman codes) to standard output.
void printCodeMap(const std::unordered_map<unsigned char, std::vector<bool>>& codeMap);
