#include "FileEncoder.hpp"
#include "FileDecoder.hpp"
#include "Encoder.hpp"
#include "Decoder.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

// Helper function to read file contents as a string
std::string readFileToString(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(in), {});
}

int main() {
    const std::string inputFile = "data/test_input.txt";
    const std::string encodedFile = "data/test_output.huff";
    const std::string restoredFile = "data/restored.txt";

    // Write test content to input.txt
    std::string originalText = "This is a test for Huffman encoding through files. ()()";
    std::ofstream out(inputFile, std::ios::binary);
    out << originalText;
    out.close();

    try {
        // Encode the input file
        FileEncoder encoder;
        encoder.encodeFile(inputFile, encodedFile);

        // Decode the .huff file
        FileDecoder decoder;
        decoder.decodeFile(encodedFile, restoredFile);

        // Compare input and restored files
        std::string restoredText = readFileToString(restoredFile);
        std::cout << "Original Text : " << originalText << "\n";
        std::cout << "Restored Text : " << restoredText << "\n";

        assert(originalText == restoredText);
        std::cout << "File encode-decode successful.\n";

        // Use Huffman tree from encoding to encode and decode a string
        std::string extraString = "Huffman";
        std::vector<unsigned char> extraData(extraString.begin(), extraString.end());

        Encoder treeBuilder;
        treeBuilder.build(std::vector<unsigned char>(originalText.begin(), originalText.end()));
        auto tree = treeBuilder.getRoot();

        std::vector<bool> encodedBits = treeBuilder.encode(extraData);

        Decoder extraDecoder;
        extraDecoder.setTree(tree);
        std::vector<unsigned char> decoded = extraDecoder.decode(encodedBits);
        std::string decodedString(decoded.begin(), decoded.end());

        std::cout << "Extra encoded-decoded: " << decodedString << "\n";
        assert(extraString == decodedString);
        std::cout << "Tree reuse for string encode-decode successful.\n";

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
