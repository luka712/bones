#include "InterleavedBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;

unsigned int InterleavedBuffer::m_idGen = 0;

InterleavedBuffer::InterleavedBuffer(const float* data, const int count, vector<BufferAttribute> attributes)
	: m_data(data), m_attributes(attributes)
{
	LOG_CONSTRUCTOR();
	m_idGen++;
	m_id = m_idGen;
	m_count = count;
}

void InterleavedBuffer::Initialize()
{
	if (m_initialized) return;
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

void InterleavedBuffer::Initialize(const unsigned int program)
{
	if (m_initialized) return;

	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		BufferAttribute attrib = m_attributes[i];

		// meaning it was not bound. attribute location can be passed in case where shader has layout(location = {location}) on attribute
		if (attrib.attributeLocation < 0)
		{
			attrib.attributeLocation = glGetAttribLocation(program, attrib.attributeLayoutName.c_str());
		}

		if (attrib.attributeLocation < 0)
		{
			if (attrib.attributeLayoutName.size() > 0)
			{
				cout << "Cannot find attribute: " << attrib.attributeLayoutName << endl;
				throw InterleavedBufferBindingError("Canot find layout: " + attrib.attributeLayoutName);
			}
			else
			{
				throw InterleavedBufferBindingError("Cannot resolve layout.");
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
		sumSize += m_attributes[i].size;
	}

	for (size_t i = 0; i < m_attributes.size(); i++)
	{
		BufferAttribute attrib = m_attributes[i];
		glEnableVertexAttribArray(attrib.attributeLocation);
		glVertexAttribPointer(attrib.attributeLocation, attrib.size, GL_FLOAT, GL_FALSE, sumSize * sizeof(float), (void*)(attrib.offset * sizeof(float)));
	}
}

void InterleavedBuffer::Destroy()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] m_data;
	DeleteBuffer();
	m_state = Bones::State::Destroyed;
}