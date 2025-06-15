#include "FileEncoder.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>  

// Helper function to get file size
std::streampos getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    return file.is_open() ? file.tellg() : std::streampos(-1);
}

// Helper function to check file existence
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main() {
    const std::string inputPath = "test_input.txt";
    const std::string outputPath = "test_output.huff";

    // Create a sample input file
    {
        std::ofstream out(inputPath, std::ios::binary);
        assert(out && "Failed to create input file");
        out << "huffman test";
    }

    // Encode the file
    try {
        FileEncoder encoder;
        encoder.encodeFile(inputPath, outputPath);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return 1;
    }

    // Validate that output file exists and has data
    assert(fileExists(outputPath) && "Output file not created");
    std::streamsize size = getFileSize(outputPath);
    assert(size > 0 && "Output file is empty");

    // Validate the first byte is a valid tree marker
    {
        std::ifstream in(outputPath, std::ios::binary);
        assert(in && "Failed to open output file");

        char marker = 0;
        in.get(marker);
        assert((marker == 'I' || marker == 'L') && "Invalid tree marker");
        std::cout << "  [OK] Tree marker = '" << marker << "'\n";
    }

    // Cleanup
    std::remove(inputPath.c_str());
    std::remove(outputPath.c_str());

    std::cout << "FileEncoder test passed.\n";
    return 0;
}
