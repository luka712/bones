#include "BaseFramebuffer.hpp"
#include "sdl_include.h"

using Bones::Framebuffers::BaseFramebuffer;

BaseFramebuffer::~BaseFramebuffer()
{
	LOG_DESTRUCTOR();
	glDeleteBuffers(1, &m_fbo);
}

void BaseFramebuffer::Bind() const 
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void BaseFramebuffer::Unbind() const 
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
