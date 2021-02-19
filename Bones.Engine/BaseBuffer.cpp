#include "BaseBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::Buffers;

BaseBuffer::BaseBuffer()
{
}

void Bones::Buffers::BaseBuffer::Load()
{
	LOG_LOAD();
	if (m_state >= State::Loaded)
	{
		LOG_FORMAT("Attribute buffer with id '%s' already loaded.", m_id.m_value.c_str());
		return;
	}
	m_state = State::Loaded;
}

void BaseBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

const std::unordered_map<std::string, Bones::Variant> BaseBuffer::CreateEventData()
{
	std::unordered_map<std::string, Bones::Variant> map;
	map.emplace("source", this);
	map.emplace("source_id", m_id.m_value);

	return map;
}
