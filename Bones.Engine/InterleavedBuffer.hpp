#pragma once

#ifndef INTERLEAVED_BUFFER_H

#define INTERLEAVED_BUFFER_H

#include <string>
#include <iostream>
#include <vector>
#include "BaseBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		using namespace std;

		struct InterleavedBufferBindingError : public exception
		{
			string m_error;

			InterleavedBufferBindingError(const string& error) : m_error(error) {}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		struct BufferAttribute 
		{
			int attributeLocation;
			string attributeLayoutName;
			int size;
			int offset;
		};

		class InterleavedBuffer : public BaseBuffer
		{		
		protected:
			const float* m_data;
			vector<BufferAttribute> m_attributes;

		public:
			// id generator, for every new instance this id is increased.
			static unsigned int m_idGen;

			// the id
			unsigned int m_id;


			InterleavedBuffer(const float *data, const int length, vector<BufferAttribute> attributes);

			void Initialize();
			void Initialize(const unsigned int program);
			void Bind();
			void Destroy();
		};
	}
}

#endif // !INTERLEAVED_BUFFER_H