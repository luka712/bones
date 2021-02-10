#include "CubeTexture.hpp"
#include "TextureLoaderDataStructs.hpp"

using Bones::Textures::CubeTexture;

CubeTexture::CubeTexture()
{
	m_textureType = GLTextureType::TEXTURE_CUBE_MAP;
}