#include "VertexBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;

VertexBuffer::VertexBuffer(const string& layoutName, const int size, const float* data, const size_t count)
	: m_layoutName(layoutName), m_size(size), m_data(data)
{
	LOG_CONSTRUCTOR();
	m_count = count;
}

VertexBuffer::VertexBuffer(const int attributeLocation, const int size, const float * data, const size_t count)
	:m_attributeLocation(attributeLocation), m_size(size), m_data(data)
{
	LOG_CONSTRUCTOR();
	m_count = count;
}


void VertexBuffer::Initialize()
{
	if (m_initialized)
	{
		LOG_WARN_FORMAT("Vertex buffer already initialized %d.",m_attributeLocation );
		return;
	}
	m_initialized = true;

	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_count, m_data, GL_STATIC_DRAW);

	// if not debug, clear data from memory.
#if DEBUG == 0
	m_data.clear();
#endif

	m_state = State::Initialized;

	Bind();
}

void VertexBuffer::Initialize(const unsigned int program)
{
	if (m_initialized)
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
			cout << "Cannot find attribute: " << m_layoutName << endl;
			// throw VertexBufferBindingError("Canot find layout: " + m_layoutName);
		}
		else
		{
			throw VertexBufferBindingError("Cannot resolve layout.");
		}
	}

	Initialize();
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glEnableVertexAttribArray(m_attributeLocation);
	glVertexAttribPointer(m_attributeLocation, m_size, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexBuffer::Destroy()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] m_data;
	DeleteBuffer();
	m_state = Bones::State::Destroyed;
}
