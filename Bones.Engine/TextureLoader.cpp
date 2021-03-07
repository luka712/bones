#include <thread>
#include "TextureLoader.hpp"
#include "TextureLoaderDataStructs.hpp"


using Bones::Loaders::TextureLoader;
using Bones::Loaders::CubeMapTextureData;
using Bones::Loaders::TextureData;
using Bones::Loaders::TextureLoaderInvalidPathError;

TextureData* TextureLoader::LoadFromFile(const std::string& filepath)
{
#if EMSCRIPTEN_RUNTIME 
	// sometimes it might contain \n or \r for new line. Remove it. 
	std::string path(filepath);
	path.erase(std::remove(path.begin(), path.end(), '\r'), path.end());
	path.erase(std::remove(path.begin(), path.end(), '\n'), path.end());
	SDL_Surface* surface = IMG_Load(path.c_str());
#else 
	SDL_Surface* surface = IMG_Load(filepath.c_str());
#endif 
	if (!surface)
	{
		std::cout << "Unable to resolve path: " << filepath << std::endl;
		throw TextureLoaderInvalidPathError(filepath);
	}

	return new TextureData(surface);
}

CubeMapTextureData* TextureLoader::LoadFromFile(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back)
{
	return new CubeMapTextureData(
		LoadFromFile(right),
		LoadFromFile(left),
		LoadFromFile(top),
		LoadFromFile(bottom),
		LoadFromFile(front),
		LoadFromFile(back)
	);
}

CubeMapTextureData* Bones::Loaders::TextureLoader::LoadFromFileAsync(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back)
{
	TextureData* texRight;
	std::thread t0([&]() -> void
	{
		texRight = LoadFromFile(right);
	});

	TextureData* texLeft;
	std::thread t1([&]() -> void
	{
		texLeft = LoadFromFile(left);
	});

	TextureData* texTop;
	std::thread t2([&]() -> void
	{
		texTop = LoadFromFile(top);
	});

	TextureData* texBottom;
	std::thread t3([&]() -> void
	{
		texBottom = LoadFromFile(bottom);
	});

	TextureData* texFront;
	std::thread t4([&]() -> void
	{
		texFront = LoadFromFile(front);
	});

	TextureData* texBack;
	std::thread t5([&]() -> void
	{
		texBack = LoadFromFile(back);
	});

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	return new CubeMapTextureData(
		texRight,
		texLeft,
		texTop,
		texBottom,
		texFront,
		texBack
	);
}
