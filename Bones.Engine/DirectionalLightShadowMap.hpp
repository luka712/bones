//#pragma once
//
//#include <iostream>
//#include <string>
//#include "BaseTexture.hpp"
//#include "core_types.h"
//#include "DirectionalShadowShader.hpp"
//
//using namespace std;
//using namespace Bones::Shader;
//using namespace Bones::Textures;
//
//namespace Bones
//{
//	namespace Shadow
//	{
//		struct ShadowMapFrameBufferError : public exception
//		{
//			string m_error;
//
//			ShadowMapFrameBufferError(const string& status)
//			{
//				m_error = "Unable to create framebuffer object. Status: " + status;
//			}
//
//			const char* what() const throw ()
//			{
//				return m_error.c_str();
//			}
//		};
//
//		/// <summary>
//		/// Shadow map. OpenGL_ES_3, OPENGL_4
//		/// </summary>
//		class DirectionalLightShadowMap
//		{
//		protected:
//			bool m_initialized = false;
//			DirectionalShadowShader* m_shader;
//			GLuint m_FBO, m_shadowMap;
//			unsigned int  m_shadowWidth, m_shadowHeight;
//
//		public:
//			DirectionalLightShadowMap();
//			DirectionalLightShadowMap(unsigned int sizeInPixels);
//
//			inline DirectionalShadowShader& GetShader() const noexcept { return *m_shader; }
//			const GLuint GetShadowMap() const noexcept { return m_shadowMap; }
//			const GLuint GetShadowWidth() const noexcept { return m_shadowWidth; }
//			const GLuint GetShadowHeight() const noexcept { return m_shadowHeight; }
//
//			void Initialize();
//
//			void BindFramebuffer();
//
//			/// <summary>
//			/// Read shadow map into texture unit offset by amount.
//			/// </summary>
//			/// <param name="textureUnit">The texture unit to read into.</param>
//			/// <param name="offset">The offset.</param>
//			void Read(GLTextureUnit textureUnit, unsigned int offset);
//
//			/// <summary>
//			/// Read shadow map into texture unit.
//			/// </summary>
//			/// <param name="textureUnit">The texture unit to read to.</param>
//			void Read(GLTextureUnit textureUnit);
//
//			~DirectionalLightShadowMap();
//
//		};
//
//	}
//}
//
