#include "IndexBuffer.hpp"
#include "core_types.h"
#include "sdl_include.h"
#include "utils.h"

using namespace Bones::Buffers;


IndexBuffer::IndexBuffer(const U32* data, const I32 count)
	:BaseBuffer()
{
	LOG_CONSTRUCTOR();

	m_name = "Index Buffer";
	m_count = count;
	m_structComponentLength = Bones::IndicesByteSize::UNSIGNED_INT;

	Bones::Utils::ArrayPtrToVectorData(data, count, m_data);
	m_length = m_data.size();
}

// takes byte data.
IndexBuffer::IndexBuffer(const U8* data, const I32 length, const Bones::IndicesByteSize byteSize)
	:BaseBuffer()
{
	LOG_CONSTRUCTOR();

	m_name = "Index Buffer";
	m_data = std::vector<U8>();
	// copy data over.
	for (size_t i = 0; i < length; i++)
	{
		m_data.push_back(data[i]);
	}
	m_length = length;
	m_structComponentLength = byteSize;

	// Set correct count
	m_count = m_length;
	m_glType = GL_UNSIGNED_BYTE;
	if (m_structComponentLength == Bones::IndicesByteSize::UNSIGNED_SHORT)
	{
		m_count /= 2;
		m_glType = GL_UNSIGNED_SHORT;
	}

	if (m_structComponentLength == Bones::IndicesByteSize::UNSIGNED_INT)
	{
		m_count /= 4;
		m_glType = GL_UNSIGNED_INT;
	}
}

Bones::Buffers::IndexBuffer::IndexBuffer()
{
	LOG_CONSTRUCTOR();
}

void IndexBuffer::Initialize_impl()
{
	if (m_state >= State::Initialized)
	{
		LOG_FORMAT("Index Buffer with id '%s' already intialized.", m_id.m_value.c_str());
	}

#if UNIT_TEST == 0 
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_length, m_data.data(), GL_STATIC_DRAW);
#endif 

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;

	m_onInitializedEventHandler.Invoke(IEvent(m_initializeEventName, Bones::EventCategory::AttributeBufferEvent,
		{
			{ "source" , Bones::Variant(this) }
		}));
}

void IndexBuffer::Initialize_impl(const U32 program)
{
	Initialize_impl();
}

void IndexBuffer::Bind_impl()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::Unbind_impl()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void Bones::Buffers::IndexBuffer::DeleteBuffer_impl()
{
	glDeleteBuffers(1, &m_buffer);
}

void IndexBuffer::Destroy_impl()
{
	LOG_DESTROY();

	if (m_state == State::Destroyed)
	{
		LOG_FORMAT("Index buffer '%s' already desroyed.", m_id.m_value.c_str());
		return;
	}

	// If not initalized, GL cannot be destroyed.
	if (m_state >= State::New && m_buffer > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		DeleteBuffer();
	}

	m_data.clear();
	m_state = Bones::State::Destroyed;

	IEvent evt = IEvent(m_destroyEventName, Bones::EventCategory::AttributeBufferEvent,
		{
			{ "source", Bones::Variant(this) }
		});
	m_onDestroyEventHandler.Invoke(evt);

	m_onInitializedEventHandler.Clear();
	m_onDestroyEventHandler.Clear();
}

IndexBuffer::~IndexBuffer()
{
	LOG_DESTRUCTOR();
}


const char* Bones::Buffers::IndexBuffer::IndicesTypeAsChar()
{
	if (m_glType == GL_UNSIGNED_BYTE)
	{
		return "unsigned byte";
	}
	else if (m_glType == GL_UNSIGNED_SHORT)
	{
		return "unsigned short";
	}
	else if (m_glType == GL_UNSIGNED_INT)
	{
		return "unsigned int";
	}

	return "type missing";
}



