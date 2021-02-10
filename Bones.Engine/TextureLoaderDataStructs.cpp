#include "TextureLoaderDataStructs.hpp"

using Bones::Loaders::CubeMapTextureData;
using Bones::Loaders::TextureData;

TextureData::TextureData(SDL_Surface* surface)
{
	m_surface = surface;
	data = surface->pixels;
	width = surface->w;
	height = surface->h;
	bitDepth = surface->format->BytesPerPixel;
}

TextureData::~TextureData()
{
	data = nullptr;
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
}

CubeMapTextureData::CubeMapTextureData(TextureData* right, TextureData* left, TextureData* top, TextureData* bottom, TextureData* front, TextureData* back)
{
	texData[0] = right;
	texData[1] = left;
	texData[2] = top;
	texData[3] = bottom;
	texData[4] = front;
	texData[5] = back;
}

CubeMapTextureData::~CubeMapTextureData()
{
	for (int i = 0; i < 6; i++)
	{
		delete texData[i];
	}
}