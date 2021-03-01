#include "BaseBuffer.hpp"
#include "core_types.h"
#include "sdl_include.h"

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

std::unordered_map<std::string, Bones::Variant> BaseBuffer::CreateEventData()
{
	std::unordered_map<std::string, Bones::Variant> data =
	{
		{ "source", Bones::Variant(this) },
		{ "source_id", Bones::Variant(m_id.m_value) }
	};

	return data;
}
