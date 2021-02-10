#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "Constants.hpp"
#include <SDL_image.h>

using namespace std;

namespace Bones
{
	namespace Loaders
	{
		struct TextureData;
		struct CubeMapTextureData;
	}

}

using Bones::Loaders::TextureData;
using Bones::Loaders::CubeMapTextureData;

namespace Bones
{
	namespace Loaders
	{

		struct TextureLoaderInvalidPathError : public exception
		{
			string m_error;

			TextureLoaderInvalidPathError(const string& filepath)
			{
				m_error = "Unable to resolve path or file: " + filepath;
			}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		class TextureLoader final
		{
		public:
			TextureData* LoadFromFile(const string& filepath);
			CubeMapTextureData* LoadFromFile(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back);
		};


	}
}
