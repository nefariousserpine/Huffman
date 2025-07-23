#ifndef HUFFMAN_ENCODER_HPP
#define HUFFMAN_ENCODER_HPP

#include "TreeNode.hpp"
#include <unordered_map>
#include <vector>

class Encoder {
    public:
        using Code = std::vector<bool>; 

        Encoder() = default;
        ~Encoder() = default;

        void build(const std::vector<unsigned char>& data);

        const std::unordered_map<unsigned char, Code>& codeMap() const {
            return codeMap_;
        }

        std::vector<bool> encode(const std::vector<unsigned char>& data) const;

        TreeNode::Ptr getRoot() const {
            return root_;
        }

    private:
        TreeNode::Ptr root_;  
        std::unordered_map<unsigned char, Code> codeMap_;  

        TreeNode::Ptr buildTree(const std::unordered_map<unsigned char, size_t>& freq) const;

        void buildCodeMap(const TreeNode::Ptr& node, Code prefix);
};

#endif
