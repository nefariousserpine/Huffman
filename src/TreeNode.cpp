// src/TreeNode.cpp
#include "TreeNode.hpp"

// Leaf-node constructor.
// Initialize with the given symbol and its count. No children.
TreeNode::TreeNode(unsigned char sym, size_t freq)
    : symbol(sym), frequency(freq), left(nullptr), right(nullptr)
{}

// Internal-node constructor.
// Combine two subtrees into a new node. Frequency is summed.
// symbol is set to 0 since it isn’t used for internal nodes.
TreeNode::TreeNode(Ptr leftChild, Ptr rightChild)
    : symbol(0),
      frequency(leftChild->frequency + rightChild->frequency),
      left(std::move(leftChild)),
      right(std::move(rightChild))
{}

// Check for leaf status.
// A node is a leaf if it has neither left nor right child.
bool TreeNode::isLeaf() const {
    return !left && !right;
}