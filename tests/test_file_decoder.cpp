#include "FileEncoder.hpp"
#include "FileDecoder.hpp"

#include <fstream>
#include <cassert>
#include <iostream>
#include <cstdio>

// Helper: read entire file into string
std::string readAll(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    assert(in && "readAll: cannot open file");
    return std::string((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
}

// Helper: check file existence
bool fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

int main() {
    const std::string inputTxt   = "data/test_input.txt";
    const std::string encodedBin = "data/test_output.huff";
    const std::string decodedTxt = "data/restored.txt";

    // Write sample input
    {
        std::ofstream out(inputTxt, std::ios::binary);
        assert(out && "Cannot create input file");
        out << "huffman roundtrip test";
    }

    // Encode -> .huff
    {
        FileEncoder fe;
        fe.encodeFile(inputTxt, encodedBin);
    }

    // Validate encoded file
    assert(fileExists(encodedBin) && "Encoded file missing");
    {
        std::ifstream in(encodedBin, std::ios::binary);
        assert(in && "Cannot open encoded file");
        char marker;
        in.get(marker);
        assert((marker == 'L' || marker == 'I') && "Bad tree marker");
    }

    // Decode -> txt
    {
        FileDecoder fd;
        fd.decodeFile(encodedBin, decodedTxt);
    }

    // Verify round‑trip
    std::string original = readAll(inputTxt);
    std::string result   = readAll(decodedTxt);
    assert(result == original && "Decoded text differs from original");

    // Cleanup
    std::remove(inputTxt.c_str());
    std::remove(encodedBin.c_str());
    std::remove(decodedTxt.c_str());

    std::cout << "FileDecoder round - trip test passed.\n";
    return 0;
}
