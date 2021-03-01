#include "BaseGeometry.hpp"
#include "core_types.h"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "InterleavedBuffer.hpp"
#include "sdl_include.h"

using Bones::Geometry::BaseGeometry;
using Bones::Buffers::VertexBuffer;
using Bones::Buffers::IndexBuffer;


BaseGeometry::BaseGeometry(VertexBuffer* positionBuffer, unsigned int count, DrawType drawType)
{
	m_drawType = drawType;
	m_elemCount = count;
	m_positionBuffer = positionBuffer;
	m_vertexBuffers.emplace_back(positionBuffer);
}

BaseGeometry::BaseGeometry(VertexBuffer* positionBuffer, IndexBuffer* indexBuffer, DrawType drawType)
{
	m_drawType = drawType;
	m_elemCount = 0;
	m_indexBuffer = indexBuffer;
	m_positionBuffer = positionBuffer;
	m_vertexBuffers.emplace_back(positionBuffer);
}

BaseGeometry::BaseGeometry(VertexBuffer* positionBuffer, VertexBuffer* textureBuffer, IndexBuffer* indexBuffer)
{
	m_elemCount = 0;
	m_indexBuffer = indexBuffer; 
	m_positionBuffer = positionBuffer;
	m_vertexBuffers.emplace_back(positionBuffer);
	m_textureBuffer = textureBuffer;
	m_vertexBuffers.emplace_back(textureBuffer);
}

BaseGeometry::BaseGeometry(VertexBuffer* positionBuffer, VertexBuffer* textureBuffer, VertexBuffer* normalBuffer, IndexBuffer* indexBuffer)
{
	m_elemCount = 0;
	m_indexBuffer = indexBuffer;
	m_positionBuffer = positionBuffer;
	m_vertexBuffers.emplace_back(positionBuffer);
	m_textureBuffer = textureBuffer;
	m_vertexBuffers.emplace_back(textureBuffer);
	m_normalsBuffer = normalBuffer;
	m_vertexBuffers.emplace_back(normalBuffer);
}

BaseGeometry::BaseGeometry(InterleavedBuffer* ib, IndexBuffer* ixBuff)
	: m_interleavedBuffer(ib), m_indexBuffer(ixBuff)
{}

BaseGeometry::BaseGeometry(InterleavedBuffer* ib, unsigned int count)
	: m_interleavedBuffer(ib), m_elemCount(count)
{
}

BaseGeometry::~BaseGeometry()
{
	m_indexBuffer = nullptr;
	m_interleavedBuffer = nullptr;
	m_positionBuffer = nullptr;
	m_textureBuffer = nullptr;
	m_normalsBuffer = nullptr;
	m_colorBuffer = nullptr;

	m_vertexBuffers.clear();

	glDeleteVertexArrays(1, &m_VAO);
}

void BaseGeometry::InitializeBuffers()
{
	// for optimization. Same geometry can be passed to multiple instances of meshes, which will try to initialize geometry.
	if (!m_initialized)
	{
		m_initialized = true;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		if (m_indexBuffer != nullptr)
		{
			m_indexBuffer->Initialize();
		}
		for (VertexBuffer*& vertexBuffer : m_vertexBuffers)
		{
			vertexBuffer->Initialize();
		}

		if (m_interleavedBuffer != nullptr)
		{
			m_interleavedBuffer->Initialize();
		}

		UnbindBuffers();
	}
}

void BaseGeometry::InitializeBuffers(const unsigned int program)
{
	// for optimization. Same geometry can be passed to multiple instances of meshes, which will try to initialize geometry.
	if (!m_initialized)
	{
		m_initialized = true;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		if (m_indexBuffer != nullptr)
		{
			m_indexBuffer->Initialize(program);
		}
		for (VertexBuffer*& vertexBuffer : m_vertexBuffers)
		{
			vertexBuffer->Initialize(program);
		}

		if (m_interleavedBuffer != nullptr)
		{
			m_interleavedBuffer->Initialize(program);
		}

		UnbindBuffers();
	}
}
void BaseGeometry::BindBuffers()
{
	glBindVertexArray(m_VAO);
	// glBindBuffers call for GL_VERTEX_ARRAY and GL_ELEMENT_ARRAY_BUFFER
	if (m_indexBuffer != nullptr)
	{
		m_indexBuffer->Bind();
	}
	// bind vertex buffers
	for (VertexBuffer*& vertexBuffer : m_vertexBuffers)
	{
		vertexBuffer->Bind();
	}
	// bind interleaved buffer
	if (m_interleavedBuffer != nullptr)
	{
		m_interleavedBuffer->Bind();
	}
}
void BaseGeometry::UnbindBuffers()
{
	// first unbind vertex array.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BaseGeometry::SetupCulling() const
{
	// culling options
	if (m_enableCulling)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(m_cullSide);
		glFrontFace(m_cullOrder);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
}

void BaseGeometry::Draw()
{
	glBindVertexArray(m_VAO);
	SetupCulling();
	if (m_indexBuffer != nullptr)
	{
		// draw type such as Triangles, Count such as 4 for 8 bytes long data of UNSIGNED_SHORTS, type such as UNSIGNED_SHORT
		glDrawElements(static_cast<GLenum>(m_drawType), m_indexBuffer->m_count, m_indexBuffer->m_glType, 0);
	}
	else
	{
		glDrawArrays(static_cast<GLenum>(m_drawType), 0, m_elemCount);
	}
	glBindVertexArray(0);
}

vector<GLfloat> BaseGeometry::GetNormalsFromVertexArray(const unsigned int* indices, const unsigned int indicesCount,
	const GLfloat* vertices, const unsigned int verticesCount)
{
	vector<GLfloat> normals(verticesCount);

	// 3 for each triangle
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		// assumes that vertex array is of length 3 per vertex. This is to be used for positions array only
		// to use vertex which can hold additional data, like textures and normals override 3 to parameter.
		unsigned int in0 = indices[i] * 3;
		unsigned int in1 = indices[i + 1] * 3;
		unsigned int in2 = indices[i + 2] * 3;

		vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		vec3 normal = -cross(v2, v1);
		normal = normalize(normal);

		normals[in0] = normal.x;
		normals[in0 + 1] = normal.y;
		normals[in0 + 2] = normal.z;

		normals[in1] = normal.x;
		normals[in1 + 1] = normal.y;
		normals[in1 + 2] = normal.z;

		normals[in2] = normal.x;
		normals[in2 + 1] = normal.y;
		normals[in2 + 2] = normal.z;
	}

	/*for (size_t i = 0; i < verticesCount / 3; i++)
	{
		glm::vec3 vec(normals[i], normals[i + 1], normals[i + 2]);
		vec = glm::normalize(vec);
		(*normals)[i] = vec.x;
		(*normals)[i + 1] = vec.y;
		(*normals)[i + 2] = vec.z;
	}*/

	return normals;
}

VertexBuffer* BaseGeometry::CreateNormalBufferFromVertexArray(const unsigned int* indices, const unsigned int indicesCount, 
	const GLfloat* vertices, const unsigned int verticesCount)
{
	auto normals = BaseGeometry::GetNormalsFromVertexArray(indices, indicesCount, vertices, verticesCount);
	return new VertexBuffer("a_normal", 3, normals.data(), normals.size());
}