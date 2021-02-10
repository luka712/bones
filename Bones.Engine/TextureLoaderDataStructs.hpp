#pragma once

#include <SDL_image.h>

namespace Bones
{
	namespace Loaders
	{
		struct TextureData final
		{
		private:
			SDL_Surface* m_surface;
		public:
			void* data;
			int width;
			int height;
			int bitDepth;

			TextureData(SDL_Surface* surface);

			~TextureData();
		};

		struct CubeMapTextureData final
		{

			TextureData* texData[6];
			CubeMapTextureData(TextureData* right, TextureData* left, TextureData* top, TextureData* bottom, TextureData* front, TextureData* back);
			
			~CubeMapTextureData();
		};
	}
}
