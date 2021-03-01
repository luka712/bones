#include "BuffersManager.hpp"
#include "core_types.h"
#include "CubeVertexBuffer.hpp"
#include "SkyboxVertexBuffer.hpp"
#include "ASSERT_MACROS.h"

using Bones::Managers::BuffersManager;

vector<std::unique_ptr<IndexBuffer>> BuffersManager::m_indexBufferCache;
vector<std::unique_ptr<VertexBuffer>> BuffersManager::m_vertexBufferCache;
vector<std::unique_ptr<InterleavedBuffer>> BuffersManager::m_interleavedBufferCache;

Bones::EventHandler<>  BuffersManager::m_onIndexBufferCreated;
Bones::EventHandler<>  BuffersManager::m_onVertexBufferCreated;
Bones::EventHandler<>  BuffersManager::m_onInterleavedBufferCreated;


IndexBuffer* BuffersManager::CreateIndexBuffer(const U32* data, const I32  length)
{
	if (data == nullptr)
	{
		std::cout << "Warning: Trying to create index buffer without data." << std::endl;
		ASSERT(true);
	}
	if (length == 0)
	{
		std::cout << "Warning: Trying to create index buffer with length being set to 0." << std::endl;
		ASSERT(true);
	}

	m_indexBufferCache.emplace_back(new IndexBuffer(data, length));
	IndexBuffer* iBuffer = &*m_indexBufferCache.back();

	// send event
	GenerateIndexBufferName(iBuffer);
	SendIndexBufferCreatedEvent(iBuffer);
	

	return iBuffer;
}

IndexBuffer* BuffersManager::CreateIndexBuffer(const U8* data, const I32  length, const Bones::IndicesByteSize byteSize)
{
	if (data == nullptr)
	{
		std::cout << "Warning: Trying to create index buffer without data." << std::endl;
		ASSERT(true)
	}
	if (length == 0)
	{
		std::cout << "Warning: Trying to create index buffer with length being set to 0." << std::endl;
		ASSERT(true);
	}
	m_indexBufferCache.emplace_back(new IndexBuffer(data, length, byteSize));
	IndexBuffer* iBuffer = &*m_indexBufferCache.back();

	// send event
	GenerateIndexBufferName(iBuffer);
	SendIndexBufferCreatedEvent(iBuffer);

	return iBuffer;
}

VertexBuffer* BuffersManager::CreateVertexBuffer(const I32  attributeLocation, const I32  size, const F32* data, const U64 length)
{
	if (attributeLocation == 0)
	{
		std::cout << "Warning: Trying to create vertex buffer with empty name." << std::endl;
	}
	if (size == 0)
	{
		std::cout << "Warning: Trying to create vertex buffer with size being set to 0." << std::endl;
	}
	if (data == nullptr)
	{
		std::cout << "Warning: Trying to create vertex buffer without data." << std::endl;
	}
	if (length == 0)
	{
		std::cout << "Warning: Trying to create vertex buffer with length being set to 0." << std::endl;
	}

	m_vertexBufferCache.emplace_back(new VertexBuffer(attributeLocation, size, data, length));
	VertexBuffer* vBuffer = &*m_vertexBufferCache.back();

	GenerateVertexBufferName(vBuffer);
	SendVertexBufferCreatedEvent(vBuffer);

	return vBuffer;
}

VertexBuffer* BuffersManager::CreateVertexBuffer(const string& layoutName, const I32  size, const F32* data, const U64 length)
{
	{
		if (layoutName == "")
		{
			std::cout << "Warning: Trying to create vertex buffer with empty name." << std::endl;
		}
		if (size == 0)
		{
			std::cout << "Warning: Trying to create vertex buffer with size being set to 0." << std::endl;
		}
		if (data == nullptr)
		{
			std::cout << "Warning: Trying to create vertex buffer without data." << std::endl;
		}
		if (length == 0)
		{
			std::cout << "Warning: Trying to create vertex buffer with length being set to 0." << std::endl;
		}

		m_vertexBufferCache.emplace_back(new VertexBuffer(layoutName, size, data, length));
		VertexBuffer* vBuffer = &*m_vertexBufferCache.back();

		GenerateVertexBufferName(vBuffer);
		SendVertexBufferCreatedEvent(vBuffer);

		return vBuffer;

	}
}

void BuffersManager::Destroy()
{
	for (auto& iBuffer : m_indexBufferCache)
	{
		iBuffer->Destroy();
	}
	m_indexBufferCache.clear();

	for (auto& vBuffer : m_vertexBufferCache)
	{
		vBuffer->Destroy();
	}
	m_vertexBufferCache.clear();

	for (auto& ivBuffer : m_interleavedBufferCache)
	{
		ivBuffer->Destroy();
	}
	m_interleavedBufferCache.clear();

	m_onIndexBufferCreated.Clear();
	m_onVertexBufferCreated.Clear();
	m_onInterleavedBufferCreated.Clear();

	// DELETE_VECTOR(m_indexBufferCache);
	// DELETE_VECTOR(m_vertexBufferCache);
	// DELETE_VECTOR(m_interleavedBufferCache);
}

void Bones::Managers::BuffersManager::GenerateIndexBufferName(IndexBuffer* ptr)
{
	Bones::Utils::GenerateName<IndexBuffer>(ptr->m_name, m_indexBufferCache, *ptr);
}

void Bones::Managers::BuffersManager::GenerateVertexBufferName(VertexBuffer* ptr)
{
	Bones::Utils::GenerateName<VertexBuffer>(ptr->m_name, m_vertexBufferCache, *ptr);
}

void Bones::Managers::BuffersManager::GenerateInterleavedBufferName(InterleavedBuffer* ptr)
{
	Bones::Utils::GenerateName<InterleavedBuffer>(ptr->m_name, m_interleavedBufferCache, *ptr);
}

void Bones::Managers::BuffersManager::SendIndexBufferCreatedEvent(IndexBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData = 
	{
		{ "index_buffer", Variant(ptr) }
	};
	m_onIndexBufferCreated.Invoke(IEvent("buffers_manager.index_buffer_created", EventCategory::AttributeBufferEvent, eventData ));
}

void Bones::Managers::BuffersManager::SendVertexBufferCreatedEvent(VertexBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData = 
	{
		{ "vertex_buffer", Variant(ptr) }
	};
	m_onVertexBufferCreated.Invoke(IEvent( "buffers_manager.vertex_buffer_created", EventCategory::AttributeBufferEvent, eventData ));
}

void Bones::Managers::BuffersManager::SendInterleavedBufferCreatedEvent(InterleavedBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData = 
	{
		{ "interleaved_buffer", Variant(ptr) }
	};
	m_onInterleavedBufferCreated.Invoke(IEvent("buffers_manager.interleaved_buffer_created", EventCategory::AttributeBufferEvent, eventData ));
}
