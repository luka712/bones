#include "VertexBuffer.hpp"
#include "core_types.h"
#include "sdl_include.h"
#include "utils.h"
#include "PRINT_LOG_MACROS.h"

using namespace Bones::Buffers;

VertexBuffer::VertexBuffer(const std::string& layoutName, const I32 size, const F32* data, const U64 count)
	: m_layoutName(layoutName), m_structSize(size)
{
	LOG_CONSTRUCTOR();
	m_name = "Vertex Buffer";
	m_count = count;
	m_length = count * sizeof(F32);
	m_structComponentLength = sizeof(F32);
	m_structLength = m_structComponentLength * m_structSize;
	m_countOfStructs = m_count / m_structSize;

	Bones::Utils::ArrayPtrToVectorData(data, count, m_data);
}

VertexBuffer::VertexBuffer(const I32 attributeLocation, const I32 size, const F32* data, const U64 count)
	:m_attributeLocation(attributeLocation), m_structSize(size)
{
	LOG_CONSTRUCTOR();
	m_name = "Vertex Buffer";
	m_count = count;
	m_length = count * sizeof(F32);
	m_structComponentLength = sizeof(F32);
	m_structLength = m_structComponentLength * m_structSize;
	m_countOfStructs = m_count / m_structSize;

	Bones::Utils::ArrayPtrToVectorData(data, count, m_data);
}

Bones::Buffers::VertexBuffer::VertexBuffer()
{
	LOG_CONSTRUCTOR();
}

void VertexBuffer::Initialize_impl()
{
	if (m_state >= Bones::State::Initialized)
	{
		LOG_FORMAT("Vertex buffer already initialized %d.", m_attributeLocation);
		return;
	}

#if UNIT_TEST == 0
	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_length, m_data.data(), GL_STATIC_DRAW);
#endif 

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;

	m_onInitializedEventHandler.Invoke(IEvent{ m_initializeEventName, EventCategory::AttributeBufferEvent,
		{
			{ "source", Bones::Variant(this) }
		}
		});

	Bind_impl();
}

void VertexBuffer::Initialize_impl(const U32 program)
{
	if (m_state >= State::Initialized)
	{
		LOG_WARN_FORMAT("Vertex buffer already initialized %s.", m_layoutName.c_str());
		return;
	}

	// meaning it was not bound. attribute location can be passed in case where shader has layout(location = {location}) on attribute
	if (m_attributeLocation < 0)
	{
		m_attributeLocation = glGetAttribLocation(program, m_layoutName.c_str());
	}

	if (m_attributeLocation < 0)
	{
		if (m_layoutName.size() > 0)
		{
			std::cerr << "Cannot find attribute: " << m_layoutName << ". Vertex buffer id: " << m_id.m_value << std::endl;
			return;
		}
		else
		{
			std::cerr << "Cannot resolve layout. Vertex buffer id: " << m_id.m_value << std::endl;
			return;
		}
	}

	Initialize_impl();
}

void VertexBuffer::Bind_impl()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glEnableVertexAttribArray(m_attributeLocation);
	glVertexAttribPointer(m_attributeLocation, m_structSize, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexBuffer::Destroy_impl()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#if DEBUG == 0
	m_data.clear();
#endif 
	DeleteBuffer_impl();
	m_state = Bones::State::Destroyed;

	m_onDestroyEventHandler.Invoke({ m_destroyEventName, EventCategory::AttributeBufferEvent, 
		{
			{ "source", Bones::Variant(this) }
		}
	});

	m_onInitializedEventHandler.Clear();
	m_onDestroyEventHandler.Clear();
}

void Bones::Buffers::VertexBuffer::Unbind_impl()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bones::Buffers::VertexBuffer::DeleteBuffer_impl()
{
	glDeleteBuffers(1, &m_buffer);
}
