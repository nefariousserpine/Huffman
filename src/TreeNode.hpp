#ifndef HUFFMAN_TREENODE_HPP
#define HUFFMAN_TREENODE_HPP

#include <memory>

class TreeNode {
    public:
        using Ptr = std::shared_ptr<TreeNode>;

        unsigned char symbol;   

        size_t frequency;

        Ptr left;
        Ptr right;

        TreeNode(unsigned char sym, size_t freq);

        TreeNode(Ptr leftChild, Ptr rightChild);

        bool isLeaf() const;

        struct Compare {
            bool operator()(const Ptr& a, const Ptr& b) const {
                return a->frequency > b->frequency;
            }
        };
};

#endif 
