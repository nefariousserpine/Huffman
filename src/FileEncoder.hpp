#ifndef FILE_ENCODER_HPP
#define FILE_ENCODER_HPP

#include <string>
#include "Encoder.hpp"

class FileEncoder {
public:
    // encode contents of input file, write the Huffman tree and encoded data to output file
    void encodeFile(const std::string& inputFile, const std::string& outputFile);

private:
    // write bits as packed bytes
    void writeBits(std::ostream& out, const std::vector<bool>& bits) const;

    // serialize the Huffman tree into a binary stream
    void serializeTree(std::ostream& out, const TreeNode::Ptr& node) const;
};

#endif
