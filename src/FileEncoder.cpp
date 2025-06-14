#include "FileEncoder.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>

void FileEncoder::encodeFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    // Read input data
    std::vector<unsigned char> inputData(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>()
    );
    in.close();

    if (inputData.empty()) {
        throw std::runtime_error("Input file is empty: " + inputFile);
    }

    // Encode data
    Encoder encoder;
    encoder.build(inputData);
    std::vector<bool> encodedBits = encoder.encode(inputData);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

    // Serialize the Huffman tree
    serializeTree(out, encoder.getRoot());

    // Write size of encoded bit stream (to know how many bits to read during decoding)
    uint64_t bitCount = encodedBits.size();
    out.write(reinterpret_cast<const char*>(&bitCount), sizeof(bitCount));

    // Write encoded bits
    writeBits(out, encodedBits);

    out.close();
}

void FileEncoder::writeBits(std::ostream& out, const std::vector<bool>& bits) const {
    unsigned char byte = 0;
    int bitIndex = 0;

    for (bool bit : bits) {
        if (bit) {
            byte |= (1 << (7 - bitIndex));
        }
        bitIndex++;
        if (bitIndex == 8) {
            out.put(byte);
            byte = 0;
            bitIndex = 0;
        }
    }

    // Write remaining bits if the last byte is not complete
    if (bitIndex > 0) {
        out.put(byte);
    }
}

void FileEncoder::serializeTree(std::ostream& out, const TreeNode::Ptr& node) const {
    if (node->isLeaf()) {
        // Write a marker for leaf node
        out.put('L');
        out.put(node->symbol);
    } else {
        // Internal node marker
        out.put('I');
        serializeTree(out, node->left);
        serializeTree(out, node->right);
    }
}
