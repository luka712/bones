#include "InterleavedBuffer.hpp"
#include "core_types.h"
#include "sdl_include.h"
#include "utils.h"

using namespace Bones::Buffers;

InterleavedBuffer::InterleavedBuffer(const F32* data, const I32 count, vector<BufferAttribute> attributes)
	: m_attributes(attributes)
{
	LOG_CONSTRUCTOR();
	m_name = "Interleaved Buffer";
	m_count = count;

	Bones::Utils::ArrayPtrToVectorData(data, count, m_data);

	m_length = m_data.size();
}


Bones::Buffers::InterleavedBuffer::InterleavedBuffer()
{
	LOG_CONSTRUCTOR();
}

void Bones::Buffers::InterleavedBuffer::Unbind_impl()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bones::Buffers::InterleavedBuffer::DeleteBuffer_impl()
{
	glDeleteBuffers(1, &m_buffer);
}


void InterleavedBuffer::Initialize_impl()
{
	LOG_INITIALIZE();
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	//							  - m_length is total buffers size, as in count of elements * sizeof(element)
	glBufferData(GL_ARRAY_BUFFER, m_length, m_data.data(), GL_STATIC_DRAW);

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;

	m_onInitializedEventHandler.Invoke(IEvent(m_initializeEventName, EventCategory::AttributeBufferEvent,
		{
			{ "source", Bones::Variant(this) }
		}));

	for (auto& attrib : m_attributes)
	{
		m_strideLength += attrib.StructLength();
		m_strideComponentsSize += attrib.m_structSize;
	}


	Bind_impl();
}

void InterleavedBuffer::Initialize_impl(const U32 program)
{
	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		BufferAttribute attrib = m_attributes[i];

		// meaning it was not bound. attribute location can be passed in case where shader has layout(location = {location}) on attribute
		if (attrib.m_attributeLocation < 0)
		{
			attrib.m_attributeLocation = glGetAttribLocation(program, attrib.m_attributeLayoutName.c_str());
		}

		if (attrib.m_attributeLocation < 0)
		{
			if (attrib.m_attributeLayoutName.size() > 0)
			{
				std::cerr << "Cannot find attribute: " << attrib.m_attributeLayoutName << "Interleaved buffer id: " << m_id.m_value << std::endl;

				return;
			}
			else
			{
				std::cerr << "Cannot resolve layout. Interleaved buffer id: " << m_id.m_value << std::endl;
				return;
			}
		}
	}

	Initialize_impl();
}


void InterleavedBuffer::Bind_impl()
{
	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		BufferAttribute attrib = m_attributes[i];
		glEnableVertexAttribArray(attrib.m_attributeLocation);
		glVertexAttribPointer(attrib.m_attributeLocation, attrib.m_structSize, GL_FLOAT, GL_FALSE, m_strideLength, (void*)(attrib.m_offsetLength));
	}
}

void InterleavedBuffer::Destroy_impl()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#if DEBUG == 0
	m_data.clear();
#endif 
	DeleteBuffer();
	m_state = Bones::State::Destroyed;

	m_onDestroyEventHandler.Invoke(IEvent(m_destroyEventName, EventCategory::AttributeBufferEvent,
		{
			{ "source", Bones::Variant(this) }
		}));

	m_onInitializedEventHandler.Clear();
	m_onDestroyEventHandler.Clear();
}
