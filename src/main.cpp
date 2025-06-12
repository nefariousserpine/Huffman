#include "Encoder.hpp"
#include "Decoder.hpp"
#include "TreeNode.hpp"
#include "PrintMap.hpp"

#include <iostream>
#include <vector>
#include <string>

int main() {
    // Input string
    std::string inputText = "huffman encoding test";
    std::vector<unsigned char> inputData(inputText.begin(), inputText.end());

    // Encode
    Encoder encoder;
    encoder.build(inputData);
    printCodeMap(encoder.getCodeMap());
    std::vector<bool> encodedBits = encoder.encode(inputData);

    std::cout << "Original text: " << inputText << "\n";
    std::cout << "Encoded bits: ";
    for (bool bit : encodedBits) {
        std::cout << bit;
    }
    std::cout << "\n";

    // Decode
    Decoder decoder;
    decoder.setTree(encoder.getRoot());
    std::vector<unsigned char> decodedData = decoder.decode(encodedBits);
    std::string decodedText(decodedData.begin(), decodedData.end());

    std::cout << "Decoded text: " << decodedText << "\n";

    return 0;
}