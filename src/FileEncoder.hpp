#ifndef FILE_ENCODER_HPP
#define FILE_ENCODER_HPP

#include <string>
#include "Encoder.hpp"

class FileEncoder {
public:
    // Encodes the contents of inputFile, writes the Huffman tree and encoded data to outputFile
    void encodeFile(const std::string& inputFile, const std::string& outputFile);

private:
    // Writes bits as packed bytes to a binary stream
    void writeBits(std::ostream& out, const std::vector<bool>& bits) const;

    // Serializes the Huffman tree into a binary stream
    void serializeTree(std::ostream& out, const TreeNode::Ptr& node) const;
};

#endif
