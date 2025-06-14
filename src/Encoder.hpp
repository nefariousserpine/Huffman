#ifndef HUFFMAN_ENCODER_HPP
#define HUFFMAN_ENCODER_HPP

#include "TreeNode.hpp"
#include <unordered_map>
#include <vector>

// Huffman Encoder
// Builds a Huffman tree from input data and generates symbol-to-code mappings for compression.
class Encoder {
    public:
        using Code = std::vector<bool>; // Bit sequence representing a Huffman code.

        Encoder() = default;
        ~Encoder() = default;

        // Builds the Huffman tree and generates the symbol-to-code mapping.
        void build(const std::vector<unsigned char>& data);

        // Returns the symbol-to-code mapping. Only valid after build().
        const std::unordered_map<unsigned char, Code>& codeMap() const {
            return codeMap_;
        }

        // Encodes the input data into a sequence of bits using the generated codes.
        std::vector<bool> encode(const std::vector<unsigned char>& data) const;

        // Returns the root node of the Huffman tree.
        TreeNode::Ptr getRoot() const {
            return root_;
        }

    private:
        TreeNode::Ptr root_;  // Root of the Huffman tree.
        std::unordered_map<unsigned char, Code> codeMap_;  // Symbol-to-code mapping.

        // Constructs the Huffman tree from symbol frequencies.
        TreeNode::Ptr buildTree(const std::unordered_map<unsigned char, size_t>& freq) const;

        // Recursively generates codes for each symbol in the tree.
        void buildCodeMap(const TreeNode::Ptr& node, Code prefix);
};

#endif
