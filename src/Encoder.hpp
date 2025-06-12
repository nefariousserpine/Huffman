// src/Encoder.hpp
#ifndef HUFFMAN_ENCODER_HPP
#define HUFFMAN_ENCODER_HPP

#include "TreeNode.hpp"
#include <unordered_map>
#include <vector>

/*
 * Huffman Encoder
 *
 * Builds a Huffman tree from input bytes, creates a map from each byte
 * to its variable-length bit sequence, and encodes data into bits.
 */
class Encoder {
public:
    using Code = std::vector<bool>;

    Encoder() = default;
    ~Encoder() = default;

    /*
     * Take raw data and build everything you need to start encoding.
     * You’ll end up with a Huffman tree and a map from symbol→bits.
     */
    void build(const std::vector<unsigned char>& data);

    /*
     * Get the symbol -> bitstring map after build().
     * Each byte maps to its Huffman code (vector<bool>).
     */
    const std::unordered_map<unsigned char, Code>& codeMap() const {
        return codeMap_;
    }

    /*
     * Turn your data into a flat sequence of bits.
     * Requires that build() has been called already.
     */
    std::vector<bool> encode(const std::vector<unsigned char>& data) const;

    /*
    * Returns the root of the Huffman tree (needed for serialization)
    */
    TreeNode::Ptr getRoot() const;

    /*
    * Returns the symbol -> bitstring mapping
    */
    const std::unordered_map<unsigned char, std::vector<bool>>& getCodeMap() const;

private:
    TreeNode::Ptr root_;                             // Top of the Huffman tree
    std::unordered_map<unsigned char, Code> codeMap_; // Byte -> its code

    /*
     * Given a frequency table, repeatedly merge the two smallest nodes
     * until we have one tree left.
     */
    TreeNode::Ptr buildTree(const std::unordered_map<unsigned char, size_t>& freq) const;

    /*
     * Walk the tree from root to leaves.
     * Going left adds a 0 bit, going right adds a 1 bit.
     * At each leaf, record the bit path as that symbol’s code.
     */
    void buildCodeMap(const TreeNode::Ptr& node, Code prefix);
};

#endif // HUFFMAN_ENCODER_HPP