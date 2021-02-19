#include "BuffersManager.hpp"
#include "Constants.hpp"
#include "CubeVertexBuffer.hpp"
#include "SkyboxVertexBuffer.hpp"

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
	Bones::Utils::GenerateName<IndexBuffer>(iBuffer->m_name, m_indexBufferCache, *iBuffer);
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
	Bones::Utils::GenerateName<IndexBuffer>(iBuffer->m_name, m_indexBufferCache, *iBuffer);
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

	Bones::Utils::GenerateName<VertexBuffer>(vBuffer->m_name, m_vertexBufferCache, *vBuffer);
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

		Bones::Utils::GenerateName<VertexBuffer>(vBuffer->m_name, m_vertexBufferCache, *vBuffer);
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

void Bones::Managers::BuffersManager::SendIndexBufferCreatedEvent(IndexBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData;
	eventData.emplace("index_buffer", Variant(ptr));
	m_onIndexBufferCreated.Invoke({ "buffers_manager.index_buffer_created", EventCategory::AttributeBufferEvent, eventData });
}

void Bones::Managers::BuffersManager::SendVertexBufferCreatedEvent(VertexBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData;
	eventData.emplace("vertex_buffer", Variant(ptr));
	m_onVertexBufferCreated.Invoke({ "buffers_manager.vertex_buffer_created", EventCategory::AttributeBufferEvent, eventData });
}

void Bones::Managers::BuffersManager::SendInterleavedBufferCreatedEvent(InterleavedBuffer* ptr)
{
	std::unordered_map<std::string, Bones::Variant> eventData;
	eventData.emplace("interleaved_buffer", Variant(ptr));
	m_onInterleavedBufferCreated.Invoke({ "buffers_manager.interleaved_buffer_created", EventCategory::AttributeBufferEvent, eventData });
}
