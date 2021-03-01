#pragma once

#ifndef CORE_TYPES_H

#define CORE_TYPES_H

#include "APP_MACROS.h"
#include "PRINT_LOG_MACROS.h"
#include <cstdint>
#include <string>
#include <ostream>
#include <sstream>
#include <random>

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


	/// <summary>
	/// Sets draw mode with or without indices.
	/// Such as glDrawArrays or glDrawElements
	/// </summary>
	enum class DrawMode
	{
		ARRAYS, ELEMENTS
	};

	/// <summary>
	/// Byte size of different types of indices that go to indices buffer.
	/// </summary>
	enum class IndicesByteSize
	{
		// NONE no indices present.
		NONE = 0,
		UNSIGNED_BYTE = 1,
		UNSIGNED_SHORT = 2,
		UNSIGNED_INT = 4
	};

	/// <summary>
	/// Sets types of drawing when calling stuff as glDrawArrays or glDrawElements
	/// for example GL_TRIANGLES, GL_LINES etc... 
	/// </summary>
	enum class DrawType
	{
		POINTS = 0x0000,
		LINES = 0x0001,
		LINE_LOOP = 0x0002,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
		TRIANGLE_FAN = 0x0006
	};

	template<typename T>
	struct Event
	{
		T m_callee;
	};

	template <typename T, typename TValue = void*>
	struct ChangeEvent
	{
		T m_callee;
		TValue m_value;
	};


	/// <summary>
	/// The static lifecycle class.
	/// Every instance goes throught it's lifecycle
	/// which consists of 
	/// -- Load          -- called right after resource creation, before Initalize is called
	/// -- Initialize    -- called right after load method, but before update
	/// -- Update		 -- update, called every frame
	/// -- Destroy		 -- self explanatory
	/// interface methods. 
	/// </summary>
	/// <typeparam name=""></typeparam>
	template<typename T>
	class IStaticLifeCycle
	{
	public:
		static Bones::State m_state;
		static void Load()
		{
			LOG_LOAD();
			T::Load_impl();
			m_state = State::Initialized;
		}

		static void Initialize()
		{
			LOG_INITIALIZE();
			T::Initialize_impl();
			m_state = State::Loaded;
		}


		static void Update(F32 dt)
		{
			T::Update_impl(dt);
		}

		static void Render()
		{
			T::Render_impl();
		}

		static void Destroy()
		{
			LOG_DESTROY();
			T::Destroy();
			m_state = State::Destroyed;
		}
	};

	/// <summary>
	/// The lifecycle class.
	/// Every instance goes throught it's lifecycle
	/// which consists of 
	/// -- Load          -- called right after resource creation, before Initalize is called
	/// -- Initialize    -- called right after load method, but before update
	/// -- Update		 -- update, called every frame
	/// -- Destroy		 -- self explanatory
	/// interface methods. 
	/// </summary>
	/// <typeparam name=""></typeparam>
	template<typename T>
	class ILifeCycle
	{
	public:
		Bones::State m_state;
		void Load()
		{
			LOG_LOAD();
			static_cast<T*>(this)->Load_impl();
			m_state = State::Initialized;
		}

		void Initialize()
		{
			LOG_INITIALIZE();
			static_cast<T*>(this)->Initialize_impl();
			m_state = State::Loaded;
		}


		void Update(F32 dt)
		{
			static_cast<T*>(this)->Update_impl(dt);
		}

		void Render()
		{
			static_cast<T*>(this)->Render_impl();
		}

		void Destroy()
		{
			LOG_DESTROY();
			static_cast<T*>(this)->Destroy_impl();
			m_state = State::Destroyed;
		}
	};
}


#endif // !CORE_TYPES_H
