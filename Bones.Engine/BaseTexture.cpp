#include "BaseTexture.hpp"
#include <iostream>
#include "TextureLoaderDataStructs.hpp"

using Bones::Textures::BaseTexture;

BaseTexture::BaseTexture() 
{
    m_textureId = 0;
}

BaseTexture::~BaseTexture()
{
    m_state = State::Destroyed;
    glDeleteTextures(1, &m_textureId);
}

void BaseTexture::LoadTexture(TextureData& texData)
{
    m_state = State::Loaded;

    m_textureType = GLTextureType::TEXTURE_2D;

    glGenTextures(1, &m_textureId);
    glBindTexture(m_textureType, m_textureId);

    int mode = GL_RGB;
    if (texData.bitDepth == 4) {
        mode = GL_RGBA;
    }

    glTexImage2D(m_textureType, 0, mode, texData.width, texData.height, 0, mode, GL_UNSIGNED_BYTE, texData.data);

    //glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(m_textureType);

    glBindTexture(m_textureType, 0);
}

void BaseTexture::LoadCubeTexture(CubeMapTextureData& textureData)
{
    m_state = State::Loaded;
    m_textureType = GLTextureType::TEXTURE_CUBE_MAP;

    glGenTextures(1, &m_textureId);
    glBindTexture(m_textureType, m_textureId);

    for (unsigned int i = 0; i < 6; i++)
    {
        TextureData& texData = *textureData.texData[i];
        int mode = GL_RGB;
        if (texData.bitDepth == 4) {
            mode = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mode, texData.width, texData.height, 0, mode, GL_UNSIGNED_BYTE, texData.data);
    }

    glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(m_textureType, 0);
}

void BaseTexture::BindTexture() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(m_textureType, m_textureId);
}

void BaseTexture::BindTexture(int samplerUnit) const
{
    glActiveTexture(GL_TEXTURE0 + samplerUnit);
    glBindTexture(m_textureType, m_textureId);
}

void BaseTexture::UnbindTexture() const
{
    glBindTexture(m_textureType, 0);
}

