#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <fstream>
#include <map>
#include <stdexcept>
#include <queue>
#include <iterator>
#include <cstdint>

#include "BitStream.h"

class HuffmanTree {
private:
	struct Node {
	public:
		Node(int frequency, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
			: Character('\0'), Frequency(frequency), Left(std::move(left)), Right(std::move(right)) {}

		Node(char character, int frequency)
			: Character(character), Frequency(frequency), Left(nullptr), Right(nullptr) {}

	public:
		bool IsLeaf() const {
			return Left == nullptr;
		}

	public:
		char Character;
		int Frequency;
		std::shared_ptr<Node> Left;
		std::shared_ptr<Node> Right;
	};

	struct Comparator {
		bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
			return a->Frequency > b->Frequency;
		}
	};

private:
	static constexpr std::string_view TOTAL_CHARS = "total_chars=";

public:
	HuffmanTree() = delete;

public:
	static void Compress(const std::string& dataFilePath, const std::string& compressedFilePath, const std::string& codeTableFilePath) {
		// 1. Read file & Calculate frequency
		// ==================================
		std::ifstream dataFile(dataFilePath, std::ios::binary);
		if (!dataFile.is_open()) {
			throw std::runtime_error("Can't open data file.");
		}

		std::string data((std::istreambuf_iterator<char>(dataFile)),
						  std::istreambuf_iterator<char>());
		dataFile.close();

		if (data.empty()) {
			throw std::invalid_argument("Can't compress empty file.");
		}

		std::map<char, int> frequencyMap;
		for (auto c : data) {
			++frequencyMap[c];
		}

		// 2. Build HuffmanTree
		// ====================
		std::shared_ptr<Node> root = BuildTree(frequencyMap);

		// 3. Build Code Table
		// ===================
		std::map<char, std::string> codes;
		BuildCodeTable(root, "", codes);

		// 4. Write Code Table File
		// ========================
		WriteCodeTable(codeTableFilePath, codes, static_cast<long>(data.length()));

		// 5. Write Huffman Code using BitWriter
		// ======================================
		std::ofstream compressedFile(compressedFilePath, std::ios::binary);
		if (!compressedFile.is_open()) {
			throw std::runtime_error("Can't create compressed file.");
		}

		BitWriter writer(compressedFile);
		for (auto c : data) {
			const std::string& code = codes.at(c);
			writer.WriteCode(code);
		}

		writer.Flush();
		compressedFile.close();
	}

	static void Decompress(const std::string& compressedFilePath, const std::string& codeTableFilePath, const std::string& decompressedFilePath) {
		// 1. Read Code Table File
		// =======================
		std::map<std::string, char> codeToChar;
		long totalChars = ReadCodeTable(codeTableFilePath, codeToChar);

		if (totalChars == 0) {
			throw std::invalid_argument("Can't decompress empty file.");
		}

		// 2. Read Compressed Data File
		// ============================
		std::ifstream compressedFile(compressedFilePath, std::ios::binary);
		if (!compressedFile.is_open()) {
			throw std::runtime_error("Can't open compressed file.");
		}

		std::vector<std::uint8_t> compressedBytes;
		compressedBytes.assign(std::istreambuf_iterator<char>(compressedFile), std::istreambuf_iterator<char>());
		compressedFile.close();

		// 3. Read data using BitReader
		// ============================
		BitReader reader(std::move(compressedBytes));
		std::string decompressedData;
		std::string currentCode;
		long decodedCharCount = 0;

		while (reader.HasNext() && decodedCharCount < totalChars) {
			currentCode += reader.Read();

			auto it = codeToChar.find(currentCode);
			if (it != codeToChar.end()) {
				decompressedData += it->second;
				++decodedCharCount;
				currentCode.clear();
			}
		}

		if (decodedCharCount != totalChars) {
			throw std::runtime_error("Compressed data is corrupted.");
		}

		// 4. Write data to decompressed file
		// ===================================
		std::ofstream decompressedFile(decompressedFilePath, std::ios::binary);
		if (!decompressedFile.is_open()) {
			throw std::runtime_error("Can't create decompressed file.");
		}
		decompressedFile << decompressedData;
		decompressedFile.close();
	}

private:
	static std::shared_ptr<Node> BuildTree(const std::map<char, int>& frequencyMap) {
		std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Comparator> pq;

		for (const auto& entry : frequencyMap) {
			pq.push(std::make_shared<Node>(entry.first, entry.second));
		}

		if (pq.size() == 1) {
			auto node = pq.top();
			pq.pop();
			return std::make_shared<Node>(node->Frequency, node, nullptr);
		}

		while (pq.size() > 1) {
			auto left = pq.top();
			pq.pop();
			auto right = pq.top();
			pq.pop();

			auto parent = std::make_shared<Node>(left->Frequency + right->Frequency, std::move(left), std::move(right));

			pq.push(std::move(parent));
		}

		return pq.top();
	}

	static void BuildCodeTable(const std::shared_ptr<Node>& node, const std::string& prefix, std::map<char, std::string>& charToCode) {
		if (node == nullptr) {
			return;
		}

		if (node->IsLeaf()) {
			charToCode[node->Character] = prefix;
			return;
		}

		BuildCodeTable(node->Left, prefix + '0', charToCode);
		BuildCodeTable(node->Right, prefix + '1', charToCode);
	}

	static void WriteCodeTable(const std::string& filePath, const std::map<char, std::string>& charToCode, long totalChars) {
		std::ofstream writer(filePath);
		if (!writer.is_open()) {
			throw std::runtime_error("Can't create code table file");
		}

		writer << TOTAL_CHARS << totalChars << "\n";
		for (const auto& entry : charToCode) {
			writer << static_cast<int>(entry.first) << ":" << entry.second << "\n";
		}
		writer.close();
	}

	// char_code:huffman_code
	static long ReadCodeTable(const std::string& filePath, std::map<std::string, char>& codeToChar) {
		std::ifstream file(filePath);
		if (!file.is_open()) {
			throw std::runtime_error("Can't open code table file.");
		}

		std::string line;
		if (!std::getline(file, line)) {
			return 0;
		}

		if (line.substr(0, TOTAL_CHARS.length()) != TOTAL_CHARS) {
			throw std::runtime_error("Invalid code table format: missing total_chars.");
		}
		long totalChars = std::stol(line.substr(TOTAL_CHARS.length()));

		while (std::getline(file, line)) {
			size_t colonPos = line.find(':');
			if (colonPos != std::string::npos && colonPos + 1 < line.length()) {
				int charCode = std::stoi(line.substr(0, colonPos));
				std::string huffmanCode = line.substr(colonPos + 1);
				codeToChar[huffmanCode] = static_cast<char>(charCode);
			}
		}

		file.close();

		return totalChars;
	}
};
