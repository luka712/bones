#include "TextureManager.hpp"
#include "TextureLoader.hpp"
#include "Texture2D.hpp"
#include "CubeTexture.hpp"
#include "TextureLoaderDataStructs.hpp"
#include "DELETE_MACROS.h"

using Bones::Managers::TextureManager;
using Bones::Loaders::TextureLoader;

map<string, long> TextureManager::m_texture2DCacheRefCount = map<string, long>();
map<string, Texture2D*> TextureManager::m_texture2DCache = map<string, Texture2D*>();

map<string, long> TextureManager::m_textureCubeCacheRefCount = map<string, long>();
map<string, CubeTexture*> TextureManager::m_textureCubeCache = map<string, CubeTexture*>();

Texture2D* TextureManager::GetOrCreateTexture2D(string path)
{
	map<string, Texture2D*>::iterator it = m_texture2DCache.find(path);
	if (it != m_texture2DCache.end())
	{
		m_texture2DCacheRefCount.at(path)++;
		return it->second;
	}

	TextureLoader loader = TextureLoader();
	TextureData* data = loader.LoadFromFile(path);

	Texture2D* texture = new Texture2D();
	texture->m_cacheKey = path;
	texture->LoadTexture(*data);
	m_texture2DCacheRefCount.emplace(path, 1);
	m_texture2DCache.emplace(path, texture);

	delete data;

	return texture;
}

CubeTexture* TextureManager::GetOrCreateCubeTexture(const string& right, const string& left, const string& top,const string& bottom, const string& front, const string& back)
{
	string combine = right + left + top + bottom + front + back;

	map<string, CubeTexture*>::iterator it = m_textureCubeCache.find(combine);
	if (it != m_textureCubeCache.end())
	{
		m_textureCubeCacheRefCount.at(combine)++;
		return it->second;
	}

	TextureLoader loader = TextureLoader();
#if USE_THREADS 
	CubeMapTextureData* data = loader.LoadFromFileAsync(right, left, top, bottom, front, back);
#else 
	CubeMapTextureData* data = loader.LoadFromFile(right, left, top, bottom, front, back);
#endif 

	CubeTexture* texture = new CubeTexture();
	texture->m_cacheKey = combine;
	texture->LoadCubeTexture(*data);
	m_textureCubeCacheRefCount.emplace(combine, 1);
	m_textureCubeCache.emplace(combine, texture);

	delete data;

	return texture;
}

void TextureManager::DeleteTexture2D(Texture2D* tex)
{
	if (tex->m_state != State::Destroyed)
	{
		long& val = m_texture2DCacheRefCount.at(tex->m_cacheKey);
		val--;

		if (val < 0) val = 0;

		if (val == 0)
		{
			m_texture2DCacheRefCount.erase(tex->m_cacheKey);
			m_texture2DCache.erase(tex->m_cacheKey);
			delete tex;
		}
	}
}

void TextureManager::DeleteCubeTexture(CubeTexture* tex)
{
	if (tex->m_state != State::Destroyed)
	{
		long& val = m_textureCubeCacheRefCount.at(tex->m_cacheKey);
		val--;

		if (val < 0) val = 0;

		if (val == 0)
		{
			m_textureCubeCacheRefCount.erase(tex->m_cacheKey);
			m_textureCubeCache.erase(tex->m_cacheKey);
			delete tex;
		}
	}
}

void TextureManager::Delete()
{
	DELETE_MAP(m_texture2DCache);
	DELETE_MAP(m_textureCubeCache);
}
