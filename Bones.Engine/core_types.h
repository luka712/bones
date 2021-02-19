#pragma once

#ifndef CORE_TYPES_H

#define CORE_TYPES_H

#include <cstdint>
#include <string>
#include <ostream>
#include <sstream>
#include <random>
#include "PRINT_LOG_MACROS.h"

namespace Bones
{
	/// <summary>
	/// State of various resources
	/// </summary>
	enum class State
	{
		New = 0,
		Loaded = 1,
		Initialized = 2,
		Destroyed = 3,
	};

	// use types such as this instead of typical compiler specific types

	typedef uint8_t U8;
	typedef int8_t I8;

	typedef uint16_t U16;
	typedef int16_t I16;

	typedef uint32_t U32;
	typedef int32_t I32;

	typedef uint64_t U64;
	typedef int64_t I64;

	typedef float F32;

	/// <summary>
	/// The variant struct, which can represent many different types.
	/// </summary>
	struct Variant final
	{
		enum class Type : U8
		{
			TYPE_POINTER,
			TYPE_INTEGER,
			TYPE_FLOAT,
			TYPE_BOOL,
			TYPE_STRING,
			TYPE_COUNT // number of unique types 
		};

		Type m_type = Type::TYPE_POINTER;

		union
		{
			std::string m_asString = "";
			void* m_asPointer;
			I32 m_asInt;
			F32 m_asFloat;
			bool m_asBool;
		};

		Variant(void* ptr)
		{
			m_type = Type::TYPE_POINTER;
			m_asPointer = ptr;
		}

		Variant(I32 val)
		{
			m_type = Type::TYPE_INTEGER;
			m_asInt = val;
		}

		Variant(F32 val)
		{
			m_type = Type::TYPE_FLOAT;
			m_asFloat = val;
		}

		Variant(bool val)
		{
			m_type = Type::TYPE_BOOL;
			m_asBool = val;
		}

		Variant(std::string val)
		{
			m_type = Type::TYPE_STRING;
			m_asString = val;
		}

		Variant(const Variant& other)
		{
			m_type = other.m_type;
			switch (m_type)
			{
			case Type::TYPE_POINTER:
				m_asPointer = other.m_asPointer;
				break;
			case Type::TYPE_BOOL:
				m_asBool = other.m_asBool;
				break;
			case Type::TYPE_FLOAT:
				m_asFloat = other.m_asFloat;
				break;
			case Type::TYPE_INTEGER:
				m_asInt = other.m_asInt;
				break;
			case Type::TYPE_STRING:
				m_asString = other.m_asString;
				break;
			default:
				LOG_FORMAT("Cannot copy Variant with type: %u", other.m_type);
				break;
			}
		}

		~Variant()
		{
			if (m_type == Type::TYPE_POINTER)
				m_asPointer = nullptr;
		}
	};

	/// <summary>
	/// The guid, which provides unique identifier for a resource.
	/// </summary>
	struct Guid final
	{
	public:
		std::string m_value;

		Guid();

		friend std::ostream& operator<<(std::ostream& stream, const Guid& v)
		{
			stream << v.m_value << std::endl;
		}

		const bool operator==(const Guid& other)
		{
			return m_value == other.m_value;
		}

		const bool operator!=(const Guid& other)
		{
			return !(*this == other);
		}

		std::string ToString()
		{
			return m_value;
		}
	private:
		U32 RandomChar();
		std::string GenerateHex(const U32 len);
	};
}


#endif // !CORE_TYPES_H
