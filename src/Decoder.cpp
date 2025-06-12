// src/Decoder.cpp
#include "Decoder.hpp"
#include <stdexcept>

void Decoder::setTree(const TreeNode::Ptr& treeRoot) {
    if (!treeRoot) {
        throw std::invalid_argument("setTree(): provided tree root is null");
    }
    root_ = treeRoot;
}

std::vector<unsigned char> Decoder::decode(const std::vector<bool>& bits) const {
    if (!root_) {
        throw std::logic_error("decode(): Huffman tree not set; call setTree() first");
    }
    if (bits.empty()) {
        return {};  // nothing to do
    }

    std::vector<unsigned char> output;

    // Start at the top of the tree
    auto node = root_;
    for (bool bit : bits) {
        // Walk left or right based on the bit
        node = bit ? node->right : node->left;
        if (!node) {
            throw std::runtime_error("decode(): bit sequence led to a null node");
        }

        // If we’ve hit a leaf, emit its symbol and reset to root
        if (node->isLeaf()) {
            output.push_back(node->symbol);
            node = root_;
        }
    }

    // Ideally, we should end exactly at the root again,
    // otherwise the bit stream ended mid-symbol.
    if (node != root_) {
        throw std::runtime_error("decode(): incomplete bit sequence (truncated code at end)");
    }

    return output;
}