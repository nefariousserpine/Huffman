# Huffman Encoding & Decoding System

This is a C++ application for compressing and decompressing data using **Huffman coding**, a lossless data compression algorithm based on variable-length prefix codes.

## 🔍 Features

- Build a Huffman tree from input data.
- Encode byte data into compact bit sequences.
- Decode compressed bitstreams back to the original data.
- Supports reading input from text files and saving encoded output as binary.
- Serializes and deserializes the Huffman tree for reproducible decoding.
- View symbol-to-bit mappings for debugging.
- Modular, testable design with separate encoder, decoder, and tree components.

## 📂 Files

- `Encoder.cpp / Encoder.hpp` – Constructs Huffman trees and encodes data into bit sequences.
- `Decoder.cpp / Decoder.hpp` – Uses the Huffman tree to decode bit sequences back into original data.
- `TreeNode.cpp / TreeNode.hpp` – Represents nodes in the Huffman tree.
- `PrintMap.cpp / PrintMap.hpp` – Prints the symbol-to-bit mapping used in encoding.
- `FileEncoder.cpp / FileEncoder.hpp` - Encodes plain text file into compressed binary format, including serialized Huffman tree and bitstream.
- `FileDecoder.cpp / FileDecoder.hpp` - Decodes previously encoded binary files by reconstructing the Huffman tree and restoring original content.
- `main.cpp` – Demonstrates encoding and decoding of example input.

## 🛠️ Build Instructions

Requires **C++17** or later.

### Using g++

```bash
g++ -std=c++17 src/main.cpp src/Encoder.cpp src/Decoder.cpp src/TreeNode.cpp src/PrintMap.cpp -o huffman
```

### Run

```bash
./huffman
```

## 🧪 Test Instructions

### Test Files

You can create test programs inside a `tests/` folder. Here’s how to build and run sample tests:

### Compile individual tests

```bash
g++ -std=c++17 -Isrc -o test_encoder tests/test_encoder.cpp src/Encoder.cpp src/TreeNode.cpp
g++ -std=c++17 -Isrc -o test_decoder tests/test_decoder.cpp src/Decoder.cpp src/TreeNode.cpp
g++ -std=c++17 -Isrc -o test_file_encoder tests/test_file_encoder.cpp src/FileEncoder.cpp src/Encoder.cpp src/Decoder.cpp src/TreeNode.cpp
g++ -std=c++17 -Isrc -o test_file_decoder tests/test_file_decoder.cpp src/FileDecoder.cpp src/FileEncoder.cpp src/Decoder.cpp src/Encoder.cpp src/TreeNode.cpp
```

### Execute

```bash
./test_encoder
./test_decoder
./test_file_encoder
./test_file_decoder
```

## 📌 Example Usage

The `main.cpp` demonstrates the following:

- Encoding the string `"huffman encoding test"`.
- Printing the encoded bitstream.
- Displaying the character-to-bits Huffman mapping.
- Decoding the bitstream 
