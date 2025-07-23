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
        return {};
    }

    std::vector<unsigned char> output;
    auto node = root_;

    for (bool bit : bits) {
        node = bit ? node->right : node->left;
        if (!node) {
            throw std::runtime_error("decode(): bit sequence led to an invalid path");
        }

        if (node->isLeaf()) {
            output.push_back(node->symbol);
            node = root_;
        }
    }

    if (node != root_) {
        throw std::runtime_error("decode(): incomplete bit sequence");
    }

    return output;
}
