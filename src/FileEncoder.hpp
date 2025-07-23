#ifndef FILE_ENCODER_HPP
#define FILE_ENCODER_HPP

#include <string>
#include "Encoder.hpp"

class FileEncoder {
public:
    void encodeFile(const std::string& inputFile, const std::string& outputFile);

private:
    void writeBits(std::ostream& out, const std::vector<bool>& bits) const;

    void serializeTree(std::ostream& out, const TreeNode::Ptr& node) const;
};

#endif
