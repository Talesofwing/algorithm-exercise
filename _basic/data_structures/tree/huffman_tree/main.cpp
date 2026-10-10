#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "HuffmanTree.h"

std::string ReadFile(const std::string& path) {
	std::ifstream file(path, std::ios::binary);
	assert(file.is_open());
	return std::string((std::istreambuf_iterator<char>(file)),
	                    std::istreambuf_iterator<char>());
}

void WriteFile(const std::string& path, const std::string& content) {
	std::ofstream file(path, std::ios::binary);
	assert(file.is_open());
	file << content;
}

void TestHuffmanTree() {
	const std::string inputPath        = "sample.txt";
	const std::string compressedPath   = "sample.bin";
	const std::string codeTablePath    = "sample.htable";
	const std::string decompressedPath = "sample_decompressed.txt";

	// Readable sample text: English, \r\n newlines, tab, ':' and Chinese (UTF-8)
	const std::string original =
		"Huffman coding is a lossless data compression algorithm.\r\n"
		"Characters that appear more often get shorter codes.\r\n"
		"\r\n"
		"aaaaaaaaaa bbbbb ccc d\r\n"
		"key:value, tab\there, symbols !@#$%^&*()\r\n"
		// "霍夫曼編碼測試" as UTF-8 bytes, so the source file encoding doesn't matter
		"\xE9\x9C\x8D\xE5\xA4\xAB\xE6\x9B\xBC\xE7\xB7\xA8\xE7\xA2\xBC\xE6\xB8\xAC\xE8\xA9\xA6\r\n";

	WriteFile(inputPath, original);

	// Compress -> Decompress
	HuffmanTree::Compress(inputPath, compressedPath, codeTablePath);
	HuffmanTree::Decompress(compressedPath, codeTablePath, decompressedPath);

	// Decompressed file must be identical to the original, byte by byte
	assert(ReadFile(decompressedPath) == original);

	// Compressed data should be smaller than the original
	const std::string compressed = ReadFile(compressedPath);
	assert(compressed.size() < original.size());

	// Missing input file should throw
	bool thrown = false;
	try {
		HuffmanTree::Compress("not_exist.txt", "not_exist.bin", "not_exist.htable");
	} catch (const std::exception&) {
		thrown = true;
	}
	assert(thrown);

	// Missing code table should throw
	thrown = false;
	try {
		HuffmanTree::Decompress(compressedPath, "not_exist.htable", "not_exist.txt");
	} catch (const std::exception&) {
		thrown = true;
	}
	assert(thrown);

	const std::string codeTable = ReadFile(codeTablePath);
	std::cout << "Original:   " << original.size() << " bytes\n"
	          << "Compressed: " << compressed.size() << " bytes\n"
	          << "Code table: " << codeTable.size() << " bytes\n\n"
	          << "--- " << codeTablePath << " ---\n"
	          << codeTable << "\n";

	std::cout << "HuffmanTree tests passed!\n";
}

int main() {
	TestHuffmanTree();

	std::cout << "All tests passed!\n";
	return 0;
}

