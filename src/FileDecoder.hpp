#ifndef FILE_DECODER_HPP
#define FILE_DECODER_HPP

#include "TreeNode.hpp"
#include "Decoder.hpp"
#include <string>
#include <vector>
#include <istream>

class FileDecoder {
public:
    void decodeFile(const std::string& inputFile, const std::string& outputFile) const;

private:
    TreeNode::Ptr deserializeTree(std::istream& in) const;

    std::vector<bool> readBits(std::istream& in, uint64_t bitCount) const;
};

#endif 
