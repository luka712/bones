#pragma once

#ifndef BUFFERS_MANAGER_H

#define BUFFERS_MANAGER_H

#include <typeinfo>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "BaseBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "InterleavedBuffer.hpp"
#include "core_types.h"
#include "EventHandler.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		class CubeVertexBuffer;
		class SkyboxVertexBuffer;
	}
}

using std::type_info;
using std::vector;
using std::string;
using Bones::Buffers::BaseBuffer;
using Bones::Buffers::IndexBuffer;
using Bones::Buffers::VertexBuffer;
using Bones::Buffers::InterleavedBuffer;
using Bones::Buffers::CubeVertexBuffer;
using Bones::Buffers::SkyboxVertexBuffer;

namespace Bones
{
	namespace Managers
	{
		/// <summary>
		/// Class responsible for creation of buffers ( gpu memory of vertices, normals, texture coordinates ... ) 
		/// Uses GetOrCreate methods, which either return instance of buffer if one already exists or create and return instance.
		/// </summary>
		class BuffersManager final
		{
		public:
			// the index buffers cache.
			static std::vector<std::unique_ptr<IndexBuffer>> m_indexBufferCache;

			// the vertex buffer cache.
			static std::vector<std::unique_ptr<VertexBuffer>> m_vertexBufferCache;

			// the interleaved buffers cache.
			static std::vector<std::unique_ptr<InterleavedBuffer>> m_interleavedBufferCache;

			static EventHandler<> m_onIndexBufferCreated;
			static EventHandler<> m_onVertexBufferCreated;
			static EventHandler<> m_onInterleavedBufferCreated;

			/// <summary>
			/// Creates the index buffer.
			/// </summary>
			/// <param name="data">The data.</param>
			/// <param name="length">The idex buffer length.</param>
			/// <returns>The index buffer pointer.</returns>
			static IndexBuffer* CreateIndexBuffer(const U32* data, const I32 length);

			/// <summary>
			/// Creates the index buffer.
			/// </summary>
			/// <param name="data">Of unsigned bytes or chars.</param>
			/// <param name="length">Length of buffer.</param>
			/// <param name="byteSize">Byte size to use.</param>
			static IndexBuffer* CreateIndexBuffer(const U8* data, const I32 length, const Bones::IndicesByteSize byteSize);

			/// <summary>
			/// Gets or creates a new instance of index buffer.
			/// If it's instance of IndexBuffer, new instance if always created.
			/// If it's derived class , instance is cached.
			/// </summary>
			/// <typeparam name="T">IndexBuffer or derived class.</typeparam>
			/// <returns>IndexBuffer ptr or derived class ptr</returns>
			template<typename T = IndexBuffer>
			static T* GetOrCreateIndexBuffer()
			{
				T* buffer = GetOrCreate<T, IndexBuffer>(m_indexBufferCache);

				GenerateIndexBufferName(buffer);
				SendIndexBufferCreatedEvent(static_cast<IndexBuffer*>(buffer));

				return buffer;
			}

			/// <summary>
			/// Creates the vertex buffer.
			/// </summary>
			/// <typeparam name="T">The type of vertex buffer.</typeparam>
			/// <returns>The vertex buffer.</returns>
			template<typename T = VertexBuffer>
			static T* GetOrCreateVertexBuffer()
			{
				T* buffer = GetOrCreate<T, VertexBuffer>(m_vertexBufferCache);

				GenerateVertexBufferName(buffer);
				SendVertexBufferCreatedEvent(static_cast<VertexBuffer*>(buffer));

				return buffer;
			}

			/// <summary>
			/// Creates vertex buffer.
			/// </summary>
			/// <param name="attributeLocation">Layout attribute location. Corresponds to glsl (layout = {attributeLocation})</param>
			/// <param name="size">Size of vertex. For example for glsl vec3 this should be 3</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of data.</param>
			/// <returns>VertexBuffer ptr.</returns>
			static VertexBuffer* CreateVertexBuffer(const I32 attributeLocation, const I32 size, const F32* data, const U64 length);

			/// <summary>
			/// Creates vertex buffer.
			/// </summary>
			/// <param name="layoutName">Layout attribute name. Corresponds to glsl attribute. For example attribute vec3 a_position.</param>
			/// <param name="size">Size of vertex. For example for glsl vec3 this should be 3</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of data.</param>
			/// <returns>VertexBuffer ptr or derived class ptr.</returns>
			static VertexBuffer* CreateVertexBuffer(const string& layoutName, const I32 size, const F32* data, const U64 length);

			/// <summary>
			/// Gets or creates interleaved buffer from cache.
			/// </summary>
			/// <typeparam name="T">The type of interleaved buffer to create.</typeparam>
			/// <returns>The interleaved buffer.</returns>
			template<typename T = InterleavedBuffer>
			static T* GetOrCreateInterleavedBuffer()
			{
				T* buffer = GetOrCreate<T, InterleavedBuffer>(m_interleavedBufferCache);

				GenerateInterleavedBufferName(buffer);
				SendInterleavedBufferCreatedEvent(static_cast<InterleavedBuffer*>(buffer));

				return buffer;
			}

			/// <summary>
			/// Destroys all the allocated buffers and clears all the data.
			/// </summary>
			static void Destroy();
		private:
			static void GenerateIndexBufferName(IndexBuffer* ptr);
			static void GenerateVertexBufferName(VertexBuffer* ptr);
			static void GenerateInterleavedBufferName(InterleavedBuffer* ptr);

			static void SendIndexBufferCreatedEvent(IndexBuffer* ptr);
			static void SendVertexBufferCreatedEvent(VertexBuffer* ptr);
			static void SendInterleavedBufferCreatedEvent(InterleavedBuffer* ptr);

			/// <summary>
			/// Generic. Used only for other templates.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <typeparam name="TBase"></typeparam>
			/// <param name="vectorCache"></param>
			/// <returns></returns> 
			// TODO: arguments
			template<typename T, typename TBase, typename ... TArgs>
			static T* GetOrCreate(vector<std::unique_ptr<TBase>>& vectorCache, TArgs&& ... args)
			{
				size_t size = vectorCache.size();
				for (size_t i = 0; i < size; i++)
				{
					TBase* uPtrRef = &*vectorCache.at(i);
					if (typeid(*uPtrRef).name() == typeid(T).name())
					{
						return static_cast<T*>(uPtrRef);
					}
				}

				vectorCache.emplace_back(new T(std::forward<TArgs>(args)...));
				std::unique_ptr<TBase>& uniquePtr = vectorCache.back();
				TBase* entry = &*uniquePtr;
				return static_cast<T*>(entry);
			}

			
		};
	}
}

#endif // !BUFFERS_MANAGER_H
