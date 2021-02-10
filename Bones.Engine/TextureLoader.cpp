#include "TextureLoader.hpp"
#include "TextureLoaderDataStructs.hpp"

using Bones::Loaders::TextureLoader;
using Bones::Loaders::CubeMapTextureData;
using Bones::Loaders::TextureData;
using Bones::Loaders::TextureLoaderInvalidPathError;

TextureData* TextureLoader::LoadFromFile(const string& filepath)
{
#if EMSCRIPTEN_RUNTIME 
    // sometimes it might contain \n or \r for new line. Remove it. 
    string path(filepath);
    path.erase(std::remove(path.begin(), path.end(), '\r'), path.end());
    path.erase(std::remove(path.begin(), path.end(), '\n'), path.end());
    SDL_Surface* surface = IMG_Load(path.c_str());
#else 
    SDL_Surface* surface = IMG_Load(filepath.c_str());
#endif 
    if (!surface)
    {
        cout << "Unable to resolve path: " << filepath << endl;
        throw TextureLoaderInvalidPathError(filepath);
    }

    return new TextureData(surface);
}

CubeMapTextureData* TextureLoader::LoadFromFile(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back)
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
