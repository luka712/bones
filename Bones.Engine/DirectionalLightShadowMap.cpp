//#include "DirectionalLightShadowMap.hpp"
//
//using namespace Bones::Shader;
//using namespace Bones::Shadow;
//
//DirectionalLightShadowMap::DirectionalLightShadowMap()
//	: DirectionalLightShadowMap(1024)
//{}
//
//DirectionalLightShadowMap::DirectionalLightShadowMap(unsigned int sizeInPixels)
//	: m_FBO(0), m_shadowMap(0), m_shadowWidth(sizeInPixels), m_shadowHeight(sizeInPixels)
//{
//	m_shader = new DirectionalShadowShader();
//}
//
//void DirectionalLightShadowMap::Initialize()
//{
//	if (m_initialized)  return;
//	m_initialized = true;
//
//	m_shader->Initialize();
//
//	glGenFramebuffers(1, &m_FBO);
//
//	glGenTextures(1, &m_shadowMap);
//	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
//#if TARGET_OPENGL_4_6
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
//#else 
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
//#endif 
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	float bColor[] = { 1,1,1,1 };
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bColor);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
//	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);
//
//
//#if TARGET_OPENGL_4
//	glDrawBuffer(GL_NONE); // if OpenGL 4
//#else 
//	const GLenum buffers[1] = { GL_NONE };
//	glDrawBuffers(0, buffers);
//#endif 
//	glReadBuffer(GL_NONE);
//
//	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
//
//	if (status != GL_FRAMEBUFFER_COMPLETE)
//	{
//		string msg = "Framebuffer Error: " + to_string(status);
//		cout << msg << "hex: " << std::hex << status << endl;
//		throw new ShadowMapFrameBufferError(msg);
//	}
//}
//
//void DirectionalLightShadowMap::BindFramebuffer()
//{
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
//}
//
//void DirectionalLightShadowMap::Read(GLTextureUnit textureUnit, unsigned int offset)
//{
//	glActiveTexture(textureUnit + offset);
//	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
//}
//
//void DirectionalLightShadowMap::Read(GLTextureUnit textureUnit)
//{
//	glActiveTexture(textureUnit);
//	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
//}
//
//DirectionalLightShadowMap::~DirectionalLightShadowMap()
//{
//	if (m_shader)
//	{
//		delete m_shader;
//		m_shader = nullptr;
//	}
//
//	glDeleteFramebuffers(1, &m_FBO);
//	glDeleteTextures(1, &m_shadowMap);
//}
