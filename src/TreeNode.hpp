#ifndef HUFFMAN_TREENODE_HPP
#define HUFFMAN_TREENODE_HPP

#include <memory>

// Represents a node in the Huffman tree.
// A leaf node holds a symbol and its frequency. 
// An internal node points to two child subtrees and stores the sum of their frequencies.
class TreeNode {
    public:
        using Ptr = std::shared_ptr<TreeNode>;

        // The symbol (0–255) stored in a leaf node.
        unsigned char symbol;   

        // Leaf Node: Frequency of the symbol. 
        // Internal Node: Sum of frequencies of both children.
        size_t frequency;

        // Left and right children. nullptr for leaf nodes.
        Ptr left;
        Ptr right;

        // Build a leaf node for 'sym' that appears 'freq' times.
        TreeNode(unsigned char sym, size_t freq);

        // Build internal node by joining two subtrees.
        TreeNode(Ptr leftChild, Ptr rightChild);

        // True if this node has no children (i.e., is a leaf).
        bool isLeaf() const;

        // Comparison functor for priority queues.
        // Ensures smallest-frequency nodes come out first.
        struct Compare {
            bool operator()(const Ptr& a, const Ptr& b) const {
                return a->frequency > b->frequency;
            }
        };
};

#endif 
