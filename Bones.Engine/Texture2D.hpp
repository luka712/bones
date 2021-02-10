#pragma once

#include <string>
#include "BaseTexture.hpp"

using std::string;

namespace Bones
{
	namespace Textures
	{
		/// <summary>
		/// Texture 2D.
		/// </summary>
		class Texture2D final : public BaseTexture
		{
		public:
			string m_path;
			Texture2D();
		};
	}
}