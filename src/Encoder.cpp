#include "Encoder.hpp"
#include <queue>
#include <stdexcept>

void Encoder::build(const std::vector<unsigned char>& data) {
    if (data.empty()) {
        throw std::invalid_argument("build(): input is empty");
    }

    std::unordered_map<unsigned char, size_t> freqTable;
    for (auto byte : data) {
        ++freqTable[byte];
    }

    root_ = buildTree(freqTable);

    codeMap_.clear();
    buildCodeMap(root_, Code{});
}

std::vector<bool> Encoder::encode(const std::vector<unsigned char>& data) const {
    if (codeMap_.empty()) {
        throw std::logic_error("encode(): build() must be called first");
    }

    std::vector<bool> bits;

    for (auto byte : data) {
        auto it = codeMap_.find(byte);
        if (it == codeMap_.end()) {
            throw std::runtime_error("encode(): symbol not found in code map");
        }
        bits.insert(bits.end(), it->second.begin(), it->second.end());
    }
    return bits;
}

TreeNode::Ptr Encoder::buildTree(const std::unordered_map<unsigned char, size_t>& freq) const {
    std::priority_queue<
        TreeNode::Ptr,
        std::vector<TreeNode::Ptr>,
        TreeNode::Compare
    > pq;

    for (const auto& kv : freq) {
        pq.push(std::make_shared<TreeNode>(kv.first, kv.second));
    }

    while (pq.size() > 1) {
        auto left  = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        pq.push(std::make_shared<TreeNode>(left, right));
    }

    return pq.top();
}

void Encoder::buildCodeMap(const TreeNode::Ptr& node, Code prefix) {
    if (node->isLeaf()) {
        codeMap_.emplace(node->symbol, prefix);
        return;
    }

    if (node->left) {
        prefix.push_back(false);
        buildCodeMap(node->left, prefix);
        prefix.pop_back();
    }

    if (node->right) {
        prefix.push_back(true);
        buildCodeMap(node->right, prefix);
    }
}
