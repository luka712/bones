#pragma once

#ifndef BASE_GEOMETRY_H

#define BASE_GEOMETRY_H

#include "glm/ext.hpp"
#include "Constants.hpp"
#include <vector>

using namespace glm;
using namespace std;

namespace Bones
{
	namespace Buffers
	{
		class IndexBuffer;
		class VertexBuffer;
		class InterleavedBuffer;
	}
}

using Bones::DrawMode;
using Bones::DrawType;
using namespace Bones::Buffers;

namespace Bones
{
	namespace Geometry
	{
		/// <summary>
		/// Geometry is just a class which holds collection of attribute buffers,
		/// such as position, texture , normals or indices buffer.
		/// </summary>
		class BaseGeometry
		{
		protected:
			bool m_initialized = false;
			unsigned int m_elemCount = 0;
			unsigned int m_VAO = -1;

			IndexBuffer* m_indexBuffer = nullptr;
			
			InterleavedBuffer* m_interleavedBuffer = nullptr;

			VertexBuffer* m_positionBuffer = nullptr;
			VertexBuffer* m_textureBuffer = nullptr;
			VertexBuffer* m_normalsBuffer = nullptr;
			VertexBuffer* m_colorBuffer = nullptr;
			// Consider chaning to struct which holds all geometry.
			vector<VertexBuffer*> m_vertexBuffers;

			void SetupCulling() const;
		public:
			DrawType m_drawType = DrawType::TRIANGLES;
#pragma region Enums

			enum CullSide
			{
				Front = 0x0404, Back = 0x0405
			};

			enum CullOrder
			{
				Clockwise = 0x0900, CounterClockwise = 0x0901
			};

#pragma endregion

#pragma region Culling Properties
			bool m_enableCulling = false;
			CullSide m_cullSide = CullSide::Back;
			CullOrder m_cullOrder = CullOrder::CounterClockwise;
#pragma endregion

			BaseGeometry(VertexBuffer* vb, unsigned int count, DrawType drawType = DrawType::TRIANGLES);
			BaseGeometry(VertexBuffer* pb, IndexBuffer* ib, DrawType drawType = DrawType::TRIANGLES);
			BaseGeometry(VertexBuffer* pb, VertexBuffer* tb, IndexBuffer* ib);
			BaseGeometry(VertexBuffer* pb, VertexBuffer* tb, VertexBuffer* nb, IndexBuffer* ib);
			BaseGeometry(InterleavedBuffer*, IndexBuffer*);
			BaseGeometry(InterleavedBuffer*, unsigned int count);

			~BaseGeometry();

			void InitializeBuffers();
			void InitializeBuffers(const unsigned int program);

			/// <summary>
			/// Bind all buffers.
			/// </summary>
			void BindBuffers();

			/// <summary>
			/// Unbindy all buffers.
			/// </summary>
			void UnbindBuffers();

			/// <summary>
			/// Draws the geometry. Calls glDrawElements or glDrawArrays.
			/// </summary>
			void Draw();

			static vector<float> GetNormalsFromVertexArray(const unsigned int* indices, const unsigned int indicesCount, const float* vertices, const unsigned int verticesCount);
			static VertexBuffer* CreateNormalBufferFromVertexArray(const unsigned int* indices, const unsigned int indicesCount, const float* vertices, const unsigned int verticesCount);
		};

	}
}

#endif // ! BASE_GEOMETRY_H