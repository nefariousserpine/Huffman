// src/Decoder.hpp
#ifndef HUFFMAN_DECODER_HPP
#define HUFFMAN_DECODER_HPP

#include "TreeNode.hpp"
#include <vector>

/*
 * Huffman Decoder
 *
 * Takes a Huffman tree and a bit sequence, then walks the tree
 * to turn bits back into the original bytes.
 */
class Decoder {
public:
    Decoder() = default;
    ~Decoder() = default;

    /*
     * Give the decoder your Huffman tree.
     * You probably got this from the Encoder (e.g., encoder.root()).
     */
    void setTree(const TreeNode::Ptr& treeRoot);

    /*
     * Take a sequence of bits and turn it back into the original bytes.
     * Traverses the tree: 0 = go left, 1 = go right. Whenever you hit
     * a leaf, emit that symbol and jump back to the root.
     */
    std::vector<unsigned char> decode(const std::vector<bool>& bits) const;

private:
    TreeNode::Ptr root_;   // Root of the Huffman tree we’ll use to decode
};

#endif // HUFFMAN_DECODER_HPP
