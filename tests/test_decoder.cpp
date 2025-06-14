#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "TreeNode.hpp"
#include "Decoder.hpp"

int main() {
    int failures = 0;

    // Test 1: Simple two-symbol tree decoding
    {
        auto left  = std::make_shared<TreeNode>('A', 1);
        auto right = std::make_shared<TreeNode>('B', 1);
        auto root  = std::make_shared<TreeNode>(left, right);

        Decoder decoder;
        decoder.setTree(root);

        std::vector<bool> bits = {0,1,0,0,1};  // A B A A B
        std::vector<unsigned char> expected = {'A','B','A','A','B'};
        try {
            auto result = decoder.decode(bits);
            if (result == expected) {
                std::cout << "[PASS] Test 1: simple decode\n";
            } else {
                std::cerr << "[FAIL] Test 1: simple decode (output mismatch)\n";
                failures++;
            }
        } catch (...) {
            std::cerr << "[FAIL] Test 1: exception thrown\n";
            failures++;
        }
    }

    // Test 2: Errors on missing tree or invalid bits
    {
        Decoder decoder;
        bool ok = false;
        try {
            std::vector<bool> bits = {0,1};
            decoder.decode(bits);
        } catch (const std::logic_error&) {
            ok = true;
        } catch (...) {}
        if (!ok) {
            std::cerr << "[FAIL] Test 2a: decode() without tree did not throw logic_error\n";
            failures++;
        } else {
            std::cout << "[PASS] Test 2a: decode() without tree throws\n";
        }

        ok = false;
        try {
            decoder.setTree(nullptr);
        } catch (const std::invalid_argument&) {
            ok = true;
        } catch (...) {}
        if (!ok) {
            std::cerr << "[FAIL] Test 2b: setTree(nullptr) did not throw invalid_argument\n";
            failures++;
        } else {
            std::cout << "[PASS] Test 2b: setTree(nullptr) throws\n";
        }

        // Single-leaf tree, invalid bit sequence
        auto leaf = std::make_shared<TreeNode>('X', 1);
        decoder.setTree(leaf);
        ok = false;
        try {
            std::vector<bool> badBits = {1};  // no right child
            decoder.decode(badBits);
        } catch (const std::runtime_error&) {
            ok = true;
        } catch (...) {}
        if (!ok) {
            std::cerr << "[FAIL] Test 2c: decode(invalid bits) did not throw runtime_error\n";
            failures++;
        } else {
            std::cout << "[PASS] Test 2c: decode(invalid bits) throws\n";
        }
    }

    return (failures == 0 ? 0 : 1);
}
