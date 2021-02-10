#include "BaseModelLoader.hpp"

using namespace Bones::Loaders;

void BaseModelLoader::LoadModel(const string& filename, ModelData& data, OptionsBitField options)
{
}

ModelData BaseModelLoader::LoadModel(const string& filename, OptionsBitField options)
{
	return ModelData();
}

BaseModelLoader::~BaseModelLoader() {}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;
using namespace Bones;

EMSCRIPTEN_BINDINGS(BaseModelLoader_JS)
{
	/*value_object<TextureData>("TextureData")
		.field("textureName", &TextureData::textureName);

	value_object<MaterialData>("MaterialData")
		.field("diffuse", &MaterialData::diffuse);

	value_object<MeshData>("MeshData")
		.field("vertices", &MeshData::vertices)
		.field("normals", &MeshData::normals)
		.field("texCoords", &MeshData::texCoords)
		.field("indices", &MeshData::indices)
		.field("materialIndex", &MeshData::materialIndex);

	register_vector <MeshData>("vector<MeshData>");
	register_vector <MaterialData>("vector<MaterialData>");

	value_object<ModelData>("ModelData")
		.field("meshes", &ModelData::meshes)
		.field("materials", &ModelData::materials);*/

	// class_<BaseModelLoader>("BaseModelLoader");
}

#endif