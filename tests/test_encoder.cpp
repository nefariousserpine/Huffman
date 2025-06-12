// tests/test_encoder.cpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "Encoder.hpp"

int main() {
    int failures = 0;

    // Test 1: code map has exactly one entry per unique symbol
    {
        std::vector<unsigned char> data = {'a','b','a','c','a','b','d'};
        Encoder encoder;
        try {
            encoder.build(data);
            const auto& cmap = encoder.codeMap();
            bool ok = (cmap.size() == 4)
                      && cmap.count('a')
                      && cmap.count('b')
                      && cmap.count('c')
                      && cmap.count('d');
            if (ok) {
                std::cout << "[PASS] Test 1: code map entries\n";
            } else {
                std::cerr << "[FAIL] Test 1: code map entries\n";
                failures++;
            }
        } catch (...) {
            std::cerr << "[FAIL] Test 1: exception thrown\n";
            failures++;
        }
    }

    // Test 2: bitstream length matches sum(freq * code length)
    {
        std::vector<unsigned char> data = {'a','b','a','c','a','b','d'};
        std::unordered_map<unsigned char, size_t> freq;
        for (auto c : data) ++freq[c];

        Encoder encoder;
        encoder.build(data);
        const auto& cmap = encoder.codeMap();

        size_t expectedBits = 0;
        for (auto const& kv : cmap) {
            expectedBits += freq[kv.first] * kv.second.size();
        }

        auto bits = encoder.encode(data);
        if (bits.size() == expectedBits) {
            std::cout << "[PASS] Test 2: bitstream length\n";
        } else {
            std::cerr << "[FAIL] Test 2: bitstream length (got "
                      << bits.size() << ", expected " << expectedBits << ")\n";
            failures++;
        }
    }

    // Test 3: errors on empty build() and encode without build()
    {
        Encoder encoder;
        bool ok = false;
        try {
            std::vector<unsigned char> empty;
            encoder.build(empty);
        } catch (const std::invalid_argument&) {
            ok = true;
        } catch (...) {}
        if (!ok) {
            std::cerr << "[FAIL] Test 3a: build(empty) did not throw invalid_argument\n";
            failures++;
        } else {
            std::cout << "[PASS] Test 3a: build(empty) throws\n";
        }

        ok = false;
        try {
            std::vector<unsigned char> some = {'x','y'};
            encoder.encode(some);
        } catch (const std::logic_error&) {
            ok = true;
        } catch (...) {}
        if (!ok) {
            std::cerr << "[FAIL] Test 3b: encode() without build did not throw logic_error\n";
            failures++;
        } else {
            std::cout << "[PASS] Test 3b: encode() without build throws\n";
        }
    }

    return (failures == 0 ? 0 : 1);
}

//  g++ -std=c++17 -O2 src/TreeNode.cpp src/Encoder.cpp tests/test_encoder.cpp -Isrc -o test_encoder
