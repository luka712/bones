#pragma once

#ifndef BUFFERS_MANAGER_H

#define BUFFERS_MANAGER_H

#include <typeinfo>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "InterleavedBuffer.hpp"
#include "Constants.hpp"

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
			/// <summary>
			/// Generic. Used only for other templates.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <typeparam name="TBase"></typeparam>
			/// <param name="vectorCache"></param>
			/// <returns></returns> 
			// TODO: arguments
			template<typename T, typename TBase>
			static T* GetOrCreate(vector<std::unique_ptr<TBase>>& vectorCache)
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

				vectorCache.emplace_back(new T());
				std::unique_ptr<TBase>& uniquePtr = vectorCache.back();
				TBase* entry = &*uniquePtr;
				return static_cast<T*>(entry);
			}

			// the index buffers cache.
			static vector<std::unique_ptr<IndexBuffer>> m_indexBufferCache;

			// the vertex buffer cache.
			static vector<std::unique_ptr<VertexBuffer>> m_vertexBufferCache;

			// the interleaved buffers cache.
			static vector<std::unique_ptr<InterleavedBuffer>> m_interleavedBufferCache;

#pragma region Events
			static std::vector < std::function<void(const Bones::Event<IndexBuffer*>)>> m_onIndexBufferCreated;
#pragma endregion



		public:


			/// <summary>
			/// Creates the index buffer.
			/// </summary>
			/// <param name="data">The data.</param>
			/// <param name="length">The idex buffer length.</param>
			/// <returns>The index buffer pointer.</returns>
			static IndexBuffer* CreateIndexBuffer(const unsigned int* data, const int length);

			/// <summary>
			/// Creates the index buffer.
			/// </summary>
			/// <param name="data">Of unsigned bytes or chars.</param>
			/// <param name="length">Length of buffer.</param>
			/// <param name="byteSize">Byte size to use.</param>
			static IndexBuffer* CreateIndexBuffer(const unsigned char* data, const int length, const Bones::IndicesByteSize byteSize);

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
				Bones::Event<IndexBuffer*> evt = { static_cast<IndexBuffer*>(buffer) };
				for (auto& cb : m_onIndexBufferCreated)
				{
					cb(evt);
				}
				return buffer;
			}

			/// <summary>
			/// OnIndexBufferCreated event. Fired whenever index buffer is created.
			/// </summary>
			/// <param name="callback">Callback</param>
			static void OnIndexBufferCreated(std::function<void(const Bones::Event<IndexBuffer*>)> callback);

			/// <summary>
			/// Creates the vertex buffer.
			/// </summary>
			/// <typeparam name="T">The type of vertex buffer.</typeparam>
			/// <returns>The vertex buffer.</returns>
			template<typename T = VertexBuffer>
			static T* GetOrCreateVertexBuffer()
			{
				return GetOrCreate<T, VertexBuffer>(m_vertexBufferCache);
			}

			/// <summary>
			/// Creates vertex buffer.
			/// </summary>
			/// <param name="attributeLocation">Layout attribute location. Corresponds to glsl (layout = {attributeLocation})</param>
			/// <param name="size">Size of vertex. For example for glsl vec3 this should be 3</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of data.</param>
			/// <returns>VertexBuffer ptr.</returns>
			static VertexBuffer* CreateVertexBuffer(const int attributeLocation, const int size, const float* data, const size_t length);

			/// <summary>
			/// Creates vertex buffer.
			/// </summary>
			/// <param name="layoutName">Layout attribute name. Corresponds to glsl attribute. For example attribute vec3 a_position.</param>
			/// <param name="size">Size of vertex. For example for glsl vec3 this should be 3</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of data.</param>
			/// <returns>VertexBuffer ptr or derived class ptr.</returns>
			static VertexBuffer* CreateVertexBuffer(const string& layoutName, const int size, const float* data, const size_t length);

			/// <summary>
			/// Gets or creates interleaved buffer from cache.
			/// </summary>
			/// <typeparam name="T">The type of interleaved buffer to create.</typeparam>
			/// <returns>The interleaved buffer.</returns>
			template<typename T = InterleavedBuffer>
			static T* GetOrCreateInterleavedBuffer()
			{
				return GetOrCreate<T, InterleavedBuffer>(m_interleavedBufferCache);
			}

			/// <summary>
			/// Destroys all the allocated buffers and clears all the data.
			/// </summary>
			static void Destroy();
		};

	}
}

#endif // !BUFFERS_MANAGER_H
