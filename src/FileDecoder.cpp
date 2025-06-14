// FileDecoder.cpp
#include "FileDecoder.hpp"
#include <fstream>
#include <stdexcept>

void FileDecoder::decodeFile(const std::string& inputFile,
                             const std::string& outputFile) const
{
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        throw std::runtime_error("decodeFile: cannot open input file: " + inputFile);
    }

    // 1) Reconstruct the Huffman tree
    TreeNode::Ptr root = deserializeTree(in);
    if (!root) {
        throw std::runtime_error("decodeFile: failed to deserialize tree");
    }

    // 2) Read the bit count
    uint64_t bitCount = 0;
    in.read(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));
    if (!in) {
        throw std::runtime_error("decodeFile: failed to read bit count");
    }

    // 3) Read the packed bitstream
    std::vector<bool> bits = readBits(in, bitCount);

    // 4) Decode to original bytes
    Decoder decoder;
    decoder.setTree(root);
    std::vector<unsigned char> decoded = decoder.decode(bits);

    // 5) Write decoded bytes to output file
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        throw std::runtime_error("decodeFile: cannot open output file: " + outputFile);
    }
    out.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
}

TreeNode::Ptr FileDecoder::deserializeTree(std::istream& in) const {
    char marker;
    if (!in.get(marker)) {
        throw std::runtime_error("deserializeTree: unexpected EOF");
    }

    if (marker == 'L') {
        // Leaf: next byte is symbol
        unsigned char sym = static_cast<unsigned char>(in.get());
        return std::make_shared<TreeNode>(sym, 0);
    } else if (marker == 'I') {
        // Internal: recursively read children
        TreeNode::Ptr left  = deserializeTree(in);
        TreeNode::Ptr right = deserializeTree(in);
        return std::make_shared<TreeNode>(left, right);
    } else {
        throw std::runtime_error("deserializeTree: invalid marker");
    }
}

std::vector<bool> FileDecoder::readBits(std::istream& in, uint64_t bitCount) const {
    std::vector<bool> bits;
    bits.reserve(bitCount);

    while (bits.size() < bitCount) {
        int byte = in.get();
        if (byte == EOF) break;
        for (int i = 7; i >= 0 && bits.size() < bitCount; --i) {
            bits.push_back(((byte >> i) & 1) != 0);
        }
    }

    if (bits.size() != bitCount) {
        throw std::runtime_error("readBits: unexpected EOF or bit count mismatch");
    }
    return bits;
}
