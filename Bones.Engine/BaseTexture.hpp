#pragma once

#include <string>
#include "core_types.h"
#include "sdl_include.h"

using std::string;

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
	namespace Textures
	{
		enum GLTextureType
		{
			TEXTURE_2D = 0x0DE1,
			TEXTURE_CUBE_MAP = 0x8513
		};

		enum GLTextureUnit
		{
			TEXTURE0 = 0x84C0,
			TEXTURE1 = 0x84C1,
			TEXTURE2 = 0x84C2,
			TEXTURE3 = 0x84C3,
			TEXTURE4 = 0x84C4,
			TEXTURE5 = 0x84C5,
			TEXTURE6 = 0x84C6,
			TEXTURE7 = 0x84C7,
			TEXTURE8 = 0x84C8,
			TEXTURE9 = 0x84C9,
			TEXTURE10 = 0x84CA,
			TEXTURE11 = 0x84CB,
			TEXTURE12 = 0x84CC,
			TEXTURE13 = 0x84CD,
			TEXTURE14 = 0x84CE,
			TEXTURE15 = 0x84CF,
			TEXTURE16 = 0x84D0,
			TEXTURE17 = 0x84D1,
			TEXTURE18 = 0x84D2,
			TEXTURE19 = 0x84D3,
			TEXTURE20 = 0x84D4,
			TEXTURE21 = 0x84D5,
			TEXTURE22 = 0x84D6,
			TEXTURE23 = 0x84D7,
			TEXTURE24 = 0x84D8,
			TEXTURE25 = 0x84D9,
			TEXTURE26 = 0x84DA,
			TEXTURE27 = 0x84DB,
			TEXTURE28 = 0x84DC,
			TEXTURE29 = 0x84DD,
			TEXTURE30 = 0x84DE,
			TEXTURE31 = 0x84DF
		};


		/// <summary>
		/// The texture.
		/// </summary>
		class BaseTexture
		{
		private:
			GLuint m_textureId;
		protected:
			GLTextureType m_textureType = GLTextureType::TEXTURE_2D;
		public:
			State m_state = State::New;
			string m_cacheKey;
			BaseTexture();
			~BaseTexture();

			/// <summary>
			/// Loads the texture.
			/// </summary>
			/// <param name="textureData">The texture data.</param>
			virtual void LoadTexture(TextureData& textureData);

			/// <summary>
			/// Loads the cube map texture.
			/// </summary>
			/// <param name="textureData">The cube map texture data.</param>
			virtual void LoadCubeTexture(CubeMapTextureData& textureData);
			
			/// <summary>
			/// Just binds the texture, without setting of active sampler.
			/// </summary>
			void BindTexture() const;

			/// <summary>
			/// Bind the texture and set sampler unit.
			/// </summary>
			void BindTexture(int samplerUnit) const;

			void UnbindTexture() const;
		};
	}
};
