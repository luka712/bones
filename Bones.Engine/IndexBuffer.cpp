#include "IndexBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;


IndexBuffer::IndexBuffer(const U32* data, const I32 count)
	:BaseBuffer()
{
	LOG_CONSTRUCTOR();

	m_name = "Index Buffer";
	m_count = count;
	m_length = count * sizeof(U32);
	m_byteSize = Bones::IndicesByteSize::UNSIGNED_INT;

	// convert unsigned integers to byte data.
	for (size_t i = 0; i < m_length; i += 4)
	{
		unsigned char ucBuffer[4];
		memcpy(&ucBuffer, (U8*)&data[i / 4], sizeof(U32));
		// TODO: simply copy the data with description to index buffer.
		m_data.push_back(ucBuffer[0]);
		m_data.push_back(ucBuffer[1]);
		m_data.push_back(ucBuffer[2]);
		m_data.push_back(ucBuffer[3]);
	}
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
	m_byteSize = byteSize;

	// Set correct count
	m_count = m_length;
	m_glType = GL_UNSIGNED_BYTE;
	if (m_byteSize == Bones::IndicesByteSize::UNSIGNED_SHORT)
	{
		m_count /= 2;
		m_glType = GL_UNSIGNED_SHORT;
	}

	if (m_byteSize == Bones::IndicesByteSize::UNSIGNED_INT)
	{
		m_count /= 4;
		m_glType = GL_UNSIGNED_INT;
	}
}

void IndexBuffer::Initialize()
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

	IEvent evt = IEvent(m_initializeEventName, Bones::EventCategory::AttributeBufferEvent,CreateEventData());

	m_onInitializedEventHandler.Invoke(evt);
}

void IndexBuffer::Initialize(const U32 program)
{
	Initialize();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::Destroy()
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

	IEvent evt = IEvent(m_destroyEventName, Bones::EventCategory::AttributeBufferEvent, CreateEventData());
	m_onDestroyEventHandler.Invoke(evt);
}

IndexBuffer::~IndexBuffer()
{
	LOG_DESTRUCTOR();
}



