#ifndef HUFFMAN_DECODER_HPP
#define HUFFMAN_DECODER_HPP

#include "TreeNode.hpp"
#include <vector>

// Huffman Decoder.
// Decodes a bit sequence into original symbols using a given Huffman tree.
class Decoder {
    public:
        Decoder() = default;
        ~Decoder() = default;

        // Sets the Huffman tree to be used for decoding.
        void setTree(const TreeNode::Ptr& treeRoot);

        // Decodes a bit sequence into a byte sequence using the Huffman tree.
        std::vector<unsigned char> decode(const std::vector<bool>& bits) const;

    private:
        TreeNode::Ptr root_; // Root of the Huffman tree.
};

#endif 
