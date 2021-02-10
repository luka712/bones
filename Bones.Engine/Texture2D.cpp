#include "Texture2D.hpp"

using Bones::Textures::Texture2D;

Texture2D::Texture2D()
	:BaseTexture()
{
	m_textureType = GLTextureType::TEXTURE_2D;
}