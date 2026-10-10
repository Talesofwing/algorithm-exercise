#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include <ostream>
#include <cstdint>
#include <utility>

class BitReader {
public:
	explicit BitReader(std::vector<std::uint8_t> bytes) : _data(std::move(bytes)), _byteIndex(0), _bitIndex(0) {}

public:
	char Read() {
		if (!HasNext()) {
			throw std::runtime_error("No more bits to read.");
		}

		std::uint8_t byte = _data[_byteIndex];
		int value = (byte >> (7 - _bitIndex)) & 1;

		++_bitIndex;
		if (_bitIndex == 8) {
			_bitIndex = 0;
			++_byteIndex;
		}

		return static_cast<char>('0' + value);
	}

	bool HasNext() const {
		return _byteIndex < _data.size();
	}

private:
	std::vector<std::uint8_t> _data;
	std::vector<std::uint8_t>::size_type _byteIndex;
	int _bitIndex;
};

class BitWriter {
public:
	explicit BitWriter(std::ostream& os) : _output(os), _byte(0), _bitIndex(0) {}
	BitWriter(const BitWriter&) = delete;

	~BitWriter() {
		try { Flush(); } catch (...) {}
	}

public:
	BitWriter& operator=(const BitWriter&) = delete;

public:
	void WriteBit(char bit) {
		if (bit != '0' && bit != '1') {
			throw std::invalid_argument("Bit must be '0' or '1'");
		}

		if (bit == '1') {
			_byte |= static_cast<std::uint8_t>(1u << (7 - _bitIndex));
		}

		++_bitIndex;
		if (_bitIndex == 8) {
			_output.put(static_cast<char>(_byte));
			_byte = 0;
			_bitIndex = 0;
		}
	}

	void WriteCode(const std::string& code) {
		for (auto bit : code) {
			WriteBit(bit);
		}
	}

	void Flush() {
		if (_bitIndex > 0) {
			_output.put(static_cast<char>(_byte));
			_byte = 0;
			_bitIndex = 0;
		}
	}

private:
	std::ostream& _output;
	std::uint8_t _byte;
	int _bitIndex;
};
