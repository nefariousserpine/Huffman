#include "TreeNode.hpp"

// Constructor for Leaf Node.
// Initialize with the given symbol and its count.
TreeNode::TreeNode(unsigned char sym, size_t freq)
    : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}

// Constructor for Internal Node.
// Combine two subtrees into a new node. Frequency is summed.
// Symbol is set to 0 for internal nodes.
TreeNode::TreeNode(Ptr leftChild, Ptr rightChild)
    : symbol(0),
      frequency(leftChild->frequency + rightChild->frequency),
      left(std::move(leftChild)),
      right(std::move(rightChild)) {}

// A node is a leaf if it has neither left nor right child.
bool TreeNode::isLeaf() const {
    return !left && !right;
}
