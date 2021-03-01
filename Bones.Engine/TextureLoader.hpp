#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "core_types.h"
#include <SDL_image.h>

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

		struct TextureLoaderInvalidPathError : public std::exception
		{
			std::string m_error;

			TextureLoaderInvalidPathError(const std::string& filepath)
			{
				m_error = "Unable to resolve path or file: " + filepath;
			}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		/// <summary>
		/// The texture loader.
		/// </summary>
		class TextureLoader final
		{
		public:
			TextureData* LoadFromFile(const std::string& filepath);
			CubeMapTextureData* LoadFromFile(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);
			CubeMapTextureData* LoadFromFileAsync(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);
		};


	}
}
