//#include "OmniDirectionalLightShadowMap.hpp"
//
//using namespace Bones::Shadow;
//
//OmniDirectionalLightShadowMap::OmniDirectionalLightShadowMap()
//	: OmniDirectionalLightShadowMap(1024)
//{
//}
//
//OmniDirectionalLightShadowMap::OmniDirectionalLightShadowMap(unsigned int sizeInPixels)
//	: m_FBO(0), m_shadowMap(0), m_shadowWidth(sizeInPixels), m_shadowHeight(sizeInPixels)
//{
//	m_shader = new OmniDirectionalShadowShader();
//}
//
//void OmniDirectionalLightShadowMap::Initialize()
//{
//	if (m_initialized) return;
//
//	m_initialized = false;
//
//	m_shader->Initialize();
//	glGenFramebuffers(1, &m_FBO);
//
//	// note cube map is bound
//	glGenTextures(1, &m_shadowMap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
//
//	// check depth component. Increate from x by one for every side of cube map.
//	for (size_t i = 0; i < 6; i++)
//	{
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
//	}
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
//	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMap, 0);
//
//	glDrawBuffer(GL_NONE);
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
//
//void OmniDirectionalLightShadowMap::BindFramebuffer()
//{
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
//}
//
//void Bones::Shadow::OmniDirectionalLightShadowMap::Read(GLenum textureUnit, unsigned int offset)
//{
//	glActiveTexture(textureUnit + offset);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
//}
//
//void OmniDirectionalLightShadowMap::Read(GLTextureUnit textureUnit, unsigned int offset)
//{
//	glActiveTexture(textureUnit + offset);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
//}
//
//void OmniDirectionalLightShadowMap::Read(GLTextureUnit textureUnit)
//{
//	glActiveTexture(textureUnit);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
//}
//
//OmniDirectionalLightShadowMap::~OmniDirectionalLightShadowMap()
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
