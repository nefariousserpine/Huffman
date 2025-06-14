#include "Encoder.hpp"
#include <queue>
#include <stdexcept>

void Encoder::build(const std::vector<unsigned char>& data) {
    if (data.empty()) {
        throw std::invalid_argument("build(): input is empty");
    }

    // Build frequency table for all symbols in the input.
    std::unordered_map<unsigned char, size_t> freqTable;
    for (auto byte : data) {
        ++freqTable[byte];
    }

    // Construct the Huffman tree from the frequency table.
    root_ = buildTree(freqTable);

    // Generate symbol-to-code mapping from the tree.
    codeMap_.clear();
    buildCodeMap(root_, Code{});
}

std::vector<bool> Encoder::encode(const std::vector<unsigned char>& data) const {
    if (codeMap_.empty()) {
        throw std::logic_error("encode(): build() must be called first");
    }

    std::vector<bool> bits;

    // Encode each symbol using the code map.
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
    // Min-heap ordered by node frequency.
    std::priority_queue<
        TreeNode::Ptr,
        std::vector<TreeNode::Ptr>,
        TreeNode::Compare
    > pq;

    // Create a leaf node for each symbol.
    for (const auto& kv : freq) {
        pq.push(std::make_shared<TreeNode>(kv.first, kv.second));
    }

    // Merge nodes until a single tree remains.
    while (pq.size() > 1) {
        auto left  = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        pq.push(std::make_shared<TreeNode>(left, right));
    }

    return pq.top();
}

void Encoder::buildCodeMap(const TreeNode::Ptr& node, Code prefix) {
    // Store code for leaf node.
    if (node->isLeaf()) {
        codeMap_.emplace(node->symbol, prefix);
        return;
    }

    // Traverse left subtree (add 0 to prefix).
    if (node->left) {
        prefix.push_back(false);
        buildCodeMap(node->left, prefix);
        prefix.pop_back();
    }

    // Traverse right subtree (add 1 to prefix).
    if (node->right) {
        prefix.push_back(true);
        buildCodeMap(node->right, prefix);
    }
}
