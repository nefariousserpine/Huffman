// FileDecoder.hpp
#ifndef FILE_DECODER_HPP
#define FILE_DECODER_HPP

#include "TreeNode.hpp"
#include "Decoder.hpp"
#include <string>
#include <vector>
#include <istream>

// FileDecoder
// Reads a file containing a serialized Huffman tree and packed bitstream,
// reconstructs the tree, decodes the bits, and writes the original bytes
// to an output file.
class FileDecoder {
public:
    // Reads inputFile (tree + bits), decodes, writes to outputFile
    void decodeFile(const std::string& inputFile, const std::string& outputFile) const;

private:
    // Rebuilds the Huffman tree from the serialized form in 'in'
    TreeNode::Ptr deserializeTree(std::istream& in) const;

    // Reads 'bitCount' bits (MSB-first) from 'in' into a vector<bool>
    std::vector<bool> readBits(std::istream& in, uint64_t bitCount) const;
};

#endif // FILE_DECODER_HPP
