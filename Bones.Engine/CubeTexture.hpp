#pragma once

#ifndef TEXTURE3D_H

#define TEXTURE3D_H

#include <string>
#include "BaseTexture.hpp"

using std::string;
using Bones::Textures::BaseTexture;
using Bones::Textures::GLTextureType;

namespace Bones
{
	namespace Textures
	{
		/// <summary>
		/// Texture 2D.
		/// </summary>
		class CubeTexture final : public BaseTexture
		{
		public:
			CubeTexture();
		};
	}
}

#endif // !TEXTURE3D_H