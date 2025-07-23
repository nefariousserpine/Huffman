#include "TreeNode.hpp"

TreeNode::TreeNode(unsigned char sym, size_t freq)
    : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(Ptr leftChild, Ptr rightChild)
    : symbol(0),
      frequency(leftChild->frequency + rightChild->frequency),
      left(std::move(leftChild)),
      right(std::move(rightChild)) {}

bool TreeNode::isLeaf() const {
    return !left && !right;
}
