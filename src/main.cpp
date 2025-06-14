#include "Encoder.hpp"
#include "Decoder.hpp"
#include "TreeNode.hpp"
#include "PrintMap.hpp"

#include <iostream>
#include <vector>
#include <string>

int main() {
    // Input text to be encoded
    std::string inputText = "huffman encoding test";
    std::vector<unsigned char> inputData(inputText.begin(), inputText.end());

    // Build the Huffman encoder and generate code map
    Encoder encoder;
    encoder.build(inputData);

    // Print the symbol-to-code mapping
    printCodeMap(encoder.codeMap());

    // Encode the input data into a sequence of bits
    std::vector<bool> encodedBits = encoder.encode(inputData);

    std::cout << "Original text: " << inputText << "\n";

    // Output the encoded bit stream
    std::cout << "Encoded bits: ";
    for (bool bit : encodedBits) {
        std::cout << bit;
    }
    std::cout << "\n";

    // Set up the decoder using the same Huffman tree
    Decoder decoder;
    decoder.setTree(encoder.getRoot());

    // Decode the bit sequence back into the original bytes
    std::vector<unsigned char> decodedData = decoder.decode(encodedBits);
    std::string decodedText(decodedData.begin(), decodedData.end());

    std::cout << "Decoded text: " << decodedText << "\n";

    return 0;
}
