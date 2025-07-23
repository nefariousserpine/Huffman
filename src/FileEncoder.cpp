#include "FileEncoder.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>

void FileEncoder::encodeFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    std::vector<unsigned char> inputData(std::istreambuf_iterator<char>(in), {});
    in.close();

    if (inputData.empty()) {
        throw std::runtime_error("Input file is empty: " + inputFile);
    }

    Encoder encoder;
    encoder.build(inputData);
    std::vector<bool> encodedBits = encoder.encode(inputData);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

    serializeTree(out, encoder.getRoot());

    uint64_t bitCount = encodedBits.size();
    std::vector<char> bytes(8);
    for (int i = 0; i < 8; ++i) {
        bytes[i] = static_cast<char>((bitCount >> (8 * i)) & 0xFF);
    }
    out.write(bytes.data(), bytes.size());

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

    if (bitIndex > 0) {
        out.put(byte);
    }
}

void FileEncoder::serializeTree(std::ostream& out, const TreeNode::Ptr& node) const {
    if (node->isLeaf()) {
        out.put('L');
        out.put(node->symbol);
    } else {
        out.put('I');
        serializeTree(out, node->left);
        serializeTree(out, node->right);
    }
}
