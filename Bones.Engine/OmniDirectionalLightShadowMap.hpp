//#pragma once
//
//#include "Texture2D.hpp"
//#include "DirectionalLightShadowMap.hpp"
//#include "OmniDirectionalShadowShader.hpp"
//
//using namespace std;
//using namespace Bones::Shader;
//using namespace Bones::Textures;
//
//namespace Bones
//{
//	namespace Shadow
//	{
//
//		/// <summary>
//		/// To be used if geometry shader is available.
//		/// </summary>
//		class OmniDirectionalLightShadowMap
//		{
//		protected:
//			bool m_initialized = false;
//			OmniDirectionalShadowShader* m_shader;
//			GLuint m_FBO, m_shadowMap;
//			unsigned int  m_shadowWidth, m_shadowHeight;
//
//		public:
//			OmniDirectionalLightShadowMap();
//			OmniDirectionalLightShadowMap(unsigned int sizeInPixels);
//
//			// getters 
//			inline OmniDirectionalShadowShader& GetShader() const noexcept { return *m_shader; }
//			const GLuint GetShadowMap() const noexcept { return m_shadowMap; }
//			const GLuint GetShadowWidth() const noexcept { return m_shadowWidth; }
//			const GLuint GetShadowHeight() const noexcept { return m_shadowHeight; }
//
//			void Initialize();
//
//			void BindFramebuffer();
//
//			/// <summary>
//			/// Read the texture unit offset by amount.
//			/// </summary>
//			/// <param name="textureUnit">The texture unit.</param>
//			/// <param name="offset">The offset.</param>
//			void Read(GLenum textureUnit, unsigned int offset);
//
//			///// <summary>
//			///// Read shadow map into texture unit offset by amount.
//			///// </summary>
//			///// <param name="textureUnit">The texture unit to read into.</param>
//			///// <param name="offset">The offset.</param>
//			void Read(GLTextureUnit textureUnit, unsigned int offset);
//
//			///// <summary>
//			///// Read shadow map into texture unit.
//			///// </summary>
//			///// <param name="textureUnit">The texture unit to read to.</param>
//			void Read(GLTextureUnit textureUnit);
//
//			~OmniDirectionalLightShadowMap();
//
//		};
//	}
//}
