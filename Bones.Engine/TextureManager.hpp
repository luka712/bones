#pragma once

#ifndef TEXTUREMANAGER_H

#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <exception>

using std::string;
using std::map;
using std::ifstream;
using std::type_info;
using std::exception;


namespace Bones
{
	namespace Textures
	{
		class Texture2D;
		class CubeTexture;
	}
}

using Bones::Textures::Texture2D;
using Bones::Textures::CubeTexture;

namespace Bones
{
	namespace Managers
	{
		/// <summary>
		/// The texture manager.
		/// </summary>
		class TextureManager
		{
		private:
			static map<string, long> m_texture2DCacheRefCount;
			static map<string, Texture2D*> m_texture2DCache;

			static map<string, long> m_textureCubeCacheRefCount;
			static map<string, CubeTexture*> m_textureCubeCache;

			struct TextureManagerCannotResolveTextureType : public exception
			{
				string m_error;

				TextureManagerCannotResolveTextureType(const type_info& type)
				{
					m_error = "Bones::Managers::TextureManager: Cannot use texture. Unable to resvole type " + string(type.name()) + ".";
				}

				const char* what() const throw ()
				{
					return m_error.c_str();
				}
			};

		public:
			static Texture2D* GetOrCreateTexture2D(string path);
			
			static CubeTexture* GetOrCreateCubeTexture(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back);

			static void DeleteTexture2D(Texture2D *tex);
			static void DeleteCubeTexture(CubeTexture* tex);


			static void Delete();
		};
	}
}

#endif 
