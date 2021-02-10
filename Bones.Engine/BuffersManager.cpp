#include "BuffersManager.hpp"
#include "Constants.hpp"
#include "CubeVertexBuffer.hpp"
#include "SkyboxVertexBuffer.hpp"

using Bones::Managers::BuffersManager;

vector<std::unique_ptr<IndexBuffer>> BuffersManager::m_indexBufferCache;
vector< std::unique_ptr<VertexBuffer>> BuffersManager::m_vertexBufferCache;
vector<std::unique_ptr<InterleavedBuffer>> BuffersManager::m_interleavedBufferCache;

std::vector < std::function<void(const Bones::Event<IndexBuffer*>)>> BuffersManager::m_onIndexBufferCreated;

IndexBuffer* BuffersManager::CreateIndexBuffer(const unsigned int* data, const int length)
{
	if (data == nullptr)
	{
		LOG("Warning: Trying to create index buffer without data.");
	}
	if (length == 0)
	{
		LOG("Warning: Trying to create index buffer with length being set to 0.");
	}

	m_indexBufferCache.emplace_back(new IndexBuffer(data, length)); 
	IndexBuffer* iBuffer = &*m_indexBufferCache.back();
	Bones::Event<IndexBuffer*> evt = { iBuffer };
	for (auto& callback : m_onIndexBufferCreated) callback(evt);
	return iBuffer;
}

IndexBuffer* BuffersManager::CreateIndexBuffer(const unsigned char* data, const int length, const Bones::IndicesByteSize byteSize)
{
	if (data == nullptr)
	{
		LOG("Warning: Trying to create index buffer without data.");
	}
	if (length == 0)
	{
		LOG("Warning: Trying to create index buffer with length being set to 0.");
	}
	m_indexBufferCache.emplace_back(new IndexBuffer(data, length, byteSize));
	IndexBuffer* iBuffer = &*m_indexBufferCache.back();
	Bones::Event<IndexBuffer*> evt = { iBuffer };
	for (auto& callback : m_onIndexBufferCreated) callback(evt);
	return iBuffer;
}

void BuffersManager::OnIndexBufferCreated(std::function<void(const Bones::Event<IndexBuffer*>)> callback)
{
	m_onIndexBufferCreated.push_back(callback);
}

VertexBuffer* BuffersManager::CreateVertexBuffer(const int attributeLocation, const int size, const float* data, const size_t length)
{
	if (attributeLocation == 0)
	{
		LOG("Warning: Trying to create vertex buffer with empty name.");
	}
	if (size == 0)
	{
		LOG("Warning: Trying to create vertex buffer with size being set to 0.");
	}
	if (data == nullptr)
	{
		LOG("Warning: Trying to create vertex buffer without data.");
	}
	if (length == 0)
	{
		LOG("Warning: Trying to create vertex buffer with length being set to 0.");
	}

	m_vertexBufferCache.emplace_back(new VertexBuffer(attributeLocation, size, data, length));
	return &**m_vertexBufferCache.end();
}

VertexBuffer* BuffersManager::CreateVertexBuffer(const string& layoutName, const int size, const float* data, const size_t length)
{
	{
		if (layoutName == "")
		{
			LOG("Warning: Trying to create vertex buffer with empty name.");
		}
		if (size == 0)
		{
			LOG("Warning: Trying to create vertex buffer with size being set to 0.");
		}
		if (data == nullptr)
		{
			LOG("Warning: Trying to create vertex buffer without data.");
		}
		if (length == 0)
		{
			LOG("Warning: Trying to create vertex buffer with length being set to 0.");
		}
		m_vertexBufferCache.emplace_back(new VertexBuffer(layoutName, size, data, length));
		return &**m_vertexBufferCache.end();

	}
}

void BuffersManager::Destroy()
{
	m_indexBufferCache.clear();
	m_vertexBufferCache.clear();
	m_interleavedBufferCache.clear();
	m_onIndexBufferCreated.clear();
	
	// DELETE_VECTOR(m_indexBufferCache);
	// DELETE_VECTOR(m_vertexBufferCache);
	// DELETE_VECTOR(m_interleavedBufferCache);
}
