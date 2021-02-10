#include "BaseBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;

BaseBuffer::BaseBuffer()
{
}

void BaseBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}