#ifndef HUFFMAN_DECODER_HPP
#define HUFFMAN_DECODER_HPP

#include "TreeNode.hpp"
#include <vector>

class Decoder {
    public:
        Decoder() = default;
        ~Decoder() = default;

        void setTree(const TreeNode::Ptr& treeRoot);

        std::vector<unsigned char> decode(const std::vector<bool>& bits) const;

    private:
        TreeNode::Ptr root_; 
};

#endif 
