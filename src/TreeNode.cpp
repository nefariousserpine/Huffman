#include "TreeNode.hpp"

// initialize leaf node with the given symbol and its frequency.
TreeNode::TreeNode(unsigned char sym, size_t freq)
    : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}

// combine two subtrees into a new node. 
TreeNode::TreeNode(Ptr leftChild, Ptr rightChild)
    : symbol(0),
      frequency(leftChild->frequency + rightChild->frequency),
      left(std::move(leftChild)),
      right(std::move(rightChild)) {}

// leaf nodes - no children nodes
bool TreeNode::isLeaf() const {
    return !left && !right;
}
