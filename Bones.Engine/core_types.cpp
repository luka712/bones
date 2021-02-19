#include "core_types.h"

using namespace Bones;

Bones::Guid::Guid()
{
	m_value = GenerateHex(32);
}

U32 Bones::Guid::RandomChar()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return dis(gen);
}

std::string Bones::Guid::GenerateHex(const U32 len)
{
	std::stringstream ss;
	for (U32 i = 0; i < len; i++) {
		const auto rc = RandomChar();
		std::stringstream hexstream;
		hexstream << std::hex << rc;
		auto hex = hexstream.str();
		ss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return ss.str();
}
