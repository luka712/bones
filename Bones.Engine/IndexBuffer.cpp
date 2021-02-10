#include "IndexBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;

unsigned int IndexBuffer::m_idGen = 0;

IndexBuffer::IndexBuffer(const unsigned int* data, const int count)
	:BaseBuffer()
{
	LOG_CONSTRUCTOR();

	m_id = m_idGen++;
	m_count = count;
	m_length = count * sizeof(unsigned int);
	m_byteSize = Bones::IndicesByteSize::UNSIGNED_INT;

	// convert unsigned integers to byte data.
	for (size_t i = 0; i < m_length; i += 4)
	{
		unsigned char ucBuffer[4];
		memcpy(&ucBuffer, (unsigned char*)&data[i / 4], sizeof(unsigned int));
		// TODO: simply copy the data with description to index buffer.
		m_data.push_back(ucBuffer[0]);
		m_data.push_back(ucBuffer[1]);
		m_data.push_back(ucBuffer[2]);
		m_data.push_back(ucBuffer[3]);
	}
}

// takes byte data.
IndexBuffer::IndexBuffer(const unsigned char* data, const int length, const Bones::IndicesByteSize byteSize)
	:BaseBuffer()
{
	LOG_CONSTRUCTOR();

	m_idGen++;
	m_id = m_idGen;
	m_data = std::vector<unsigned char>();
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
	if (m_initialized) return;
	m_initialized = true;
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_length, m_data.data(), GL_STATIC_DRAW);

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;
}

void IndexBuffer::Initialize(const unsigned int program)
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_data.clear();
	DeleteBuffer();
	m_state = Bones::State::Destroyed;
}
