#include "InterleavedBuffer.hpp"
#include "core_types.h"
#include "sdl_include.h"

using namespace Bones::Buffers;

InterleavedBuffer::InterleavedBuffer(const F32* data, const I32 count, vector<BufferAttribute> attributes)
	: m_data(data), m_attributes(attributes)
{
	LOG_CONSTRUCTOR();
	m_name = "Interleaved Buffer";
	m_count = count;
}

void InterleavedBuffer::Initialize()
{
	LOG_INITIALIZE();
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(F32) * m_count, m_data, GL_STATIC_DRAW);

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;

	m_onInitializedEventHandler.Invoke(IEvent( m_initializeEventName, EventCategory::AttributeBufferEvent, CreateEventData() ));

	Bind();
}

void InterleavedBuffer::Initialize(const U32 program)
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

	Initialize();
}


void InterleavedBuffer::Bind()
{
	int sumSize = 0;
	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		sumSize += m_attributes[i].m_size;
	}

	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		BufferAttribute attrib = m_attributes[i];
		glEnableVertexAttribArray(attrib.m_attributeLocation);
		glVertexAttribPointer(attrib.m_attributeLocation, attrib.m_size, GL_FLOAT, GL_FALSE, sumSize * sizeof(F32), (void*)(attrib.m_offset * sizeof(F32)));
	}
}

void InterleavedBuffer::Destroy()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] m_data;
	DeleteBuffer();
	m_state = Bones::State::Destroyed;

	m_onDestroyEventHandler.Invoke(IEvent(m_destroyEventName, EventCategory::AttributeBufferEvent, CreateEventData() ));
}
