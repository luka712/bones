#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BaseBuffer.hpp"

using namespace std;

namespace Bones
{
	namespace Buffers
	{

		struct VertexBufferBindingError : public exception
		{
			string m_error;

			VertexBufferBindingError(const string& error) : m_error(error) {}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		class VertexBuffer : public BaseBuffer
		{
		protected:
			const float* m_data;
			string m_layoutName;
			int m_size;
			int m_attributeLocation = -1;

		public:
			VertexBuffer(const string& layoutName, const int size, const float* data, const size_t length);
			VertexBuffer(const int attributeLocation, const int size, const float* data, const size_t length);


			void Initialize() override;
			void Initialize(const unsigned int program) override;
			void Bind() override ;

			void Destroy();
		};
	}
}
