#include "PostProcessFramebuffer.hpp"
#include "BasePostProcessShader.hpp"
#include "GeometryManager.hpp"
#include "QuadScreenGeometry.hpp"
#include "core_types.h"
#include <iostream>

using Bones::Framebuffers::PostProcess::PostProcessFramebuffer;
using Bones::Managers::GeometryManager;

PostProcessFramebuffer::PostProcessFramebuffer(BasePostProcessShader* basePostProcessShader)
{
	LOG_CONSTRUCTOR();
	m_postProcessShader = basePostProcessShader;
	m_renderBufferObject = 0;
	m_textureId = 0;
	m_quadScreenGeometry = GeometryManager::GetOrCreateQuadScreenGeometry();
}

PostProcessFramebuffer::~PostProcessFramebuffer()
{
	LOG_DESTRUCTOR();
	Destroy();
}

void PostProcessFramebuffer::Load_impl()
{
	m_onLoad();
}

void PostProcessFramebuffer::BindUniforms_impl()
{
	m_onBindUniforms();
}

void PostProcessFramebuffer::Initialize_impl()
{
#if DEBUG
	// just throw debug message.
	if (m_state >= State::Initialized)
	{
		LOG_FORMAT("Framebuffer %s already initialized.", typeid(this).name());
	}
#endif 

	if (m_state >= State::Initialized) return;

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	int width = DEFAULT_WIDTH;
	int height = DEFAULT_HEIGHT;

	// create a color attachment texture
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);


	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_onInitialized();
}

void PostProcessFramebuffer::Destroy_impl()
{
	glDeleteTextures(1, &m_textureId);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
	glDeleteFramebuffers(1, &m_fbo);
}

void PostProcessFramebuffer::Render_impl()
{
	Render(0);
}

void PostProcessFramebuffer::Render(U32 renderBufferObject)
{
	// which framebuffer to bind to.
	glBindFramebuffer(GL_FRAMEBUFFER, renderBufferObject);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	// clear all relevant buffers
	glClear(GL_COLOR_BUFFER_BIT);

	// use the shader.
	m_postProcessShader->UseProgram();

	// texture location should look at unit 0
	m_postProcessShader->SetInt(m_postProcessShader->m_textureLocation, 0);
	// Set the actual active unit.
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, m_textureId);	// use the color attachment texture as the texture of the quad plane

	// attributes
	BindUniforms();

	m_quadScreenGeometry->Draw();
}

void Bones::Framebuffers::PostProcess::PostProcessFramebuffer::AddValue(const std::string& prop, Bones::Variant val, ValueType type, const std::string& name)
{
	PostProcessFramebufferValue v =
	{
		type,
		m_postProcessShader->m_locationsMap[prop],
		val
	};

	if(name == "")
		m_values.emplace(std::make_pair(prop, v));
	else 
		m_values.emplace(std::make_pair(name, v));
}


