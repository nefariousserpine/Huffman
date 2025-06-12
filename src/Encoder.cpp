// src/Encoder.cpp
#include "Encoder.hpp"
#include <queue>
#include <stdexcept>

void Encoder::build(const std::vector<unsigned char>& data) {
    if (data.empty()) {
        throw std::invalid_argument("build(): input is empty");
    }

    // Count how often each byte shows up
    std::unordered_map<unsigned char, size_t> freqTable;
    for (auto byte : data) {
        ++freqTable[byte];
    }

    // Convert the counts into a Huffman tree
    root_ = buildTree(freqTable);

    // Construct the byte -> bits map
    codeMap_.clear();
    buildCodeMap(root_, Code{});
}

std::vector<bool> Encoder::encode(const std::vector<unsigned char>& data) const {
    if (codeMap_.empty()) {
        throw std::logic_error("encode(): need to call build() first");
    }

    std::vector<bool> bits;

    // Look up each byte’s code and append it
    for (auto byte : data) {
        auto it = codeMap_.find(byte);
        if (it == codeMap_.end()) {
            throw std::runtime_error("encode(): symbol not in code map");
        }
        bits.insert(bits.end(), it->second.begin(), it->second.end());
    }
    return bits;
}

TreeNode::Ptr Encoder::buildTree(const std::unordered_map<unsigned char, size_t>& freq) const {
    // Min-heap that pops the node with smallest frequency first
    std::priority_queue<
        TreeNode::Ptr,
        std::vector<TreeNode::Ptr>,
        TreeNode::Compare
    > pq;

    // Start with each byte as its own leaf
    for (auto const& kv : freq) {
        pq.push(std::make_shared<TreeNode>(kv.first, kv.second));
    }

    // Merge until there’s only one tree left
    while (pq.size() > 1) {
        auto left  = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        pq.push(std::make_shared<TreeNode>(left, right));
    }

    return pq.top();
}

void Encoder::buildCodeMap(const TreeNode::Ptr& node, Code prefix) {
    // If this is a leaf, save the prefix as its code
    if (node->isLeaf()) {
        codeMap_.emplace(node->symbol, prefix);
        return;
    }

    // Otherwise, go left (0) then right (1)
    if (node->left) {
        prefix.push_back(false);
        buildCodeMap(node->left, prefix);
        prefix.pop_back();
    }
    if (node->right) {
        prefix.push_back(true);
        buildCodeMap(node->right, prefix);
        // No need to pop here since prefix is local to each call
    }
}

TreeNode::Ptr Encoder::getRoot() const {
    return root_;
}

const std::unordered_map<unsigned char, std::vector<bool>>& Encoder::getCodeMap() const {
    return codeMap_;
}