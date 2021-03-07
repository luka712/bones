// https://github.com/tinyobjloader/tinyobjloader
#define TINYGLTF_IMPLEMENTATION
#if !EMSCRIPTEN
#define STBI_MSC_SECURE_CRT
#endif 
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include <string>
#include "core_types.h"
#include "TinyGltfLoader.hpp"
#include "ASSERT_MACROS.h"


using std::string;
using Bones::DrawMode;
using Bones::DrawType;
using Bones::Vendor::TinyGltfLoader;

int TinyGltfLoader::FindIndicesBufferIndex(std::vector<TinyGltfLoader::CacheMap>& cache, tinygltf::Model& tinyModel, tinygltf::Primitive& primitive, ModelData& modelData)
{
	tinygltf::Accessor& accessor = tinyModel.accessors.at(primitive.indices);
	tinygltf::BufferView& bufferView = tinyModel.bufferViews.at(accessor.bufferView);
	tinygltf::Buffer& buffer = tinyModel.buffers.at(bufferView.buffer);

	// Set correct type of indices byte size
	Bones::IndicesByteSize byteSize = Bones::IndicesByteSize::NONE;
	if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) byteSize = Bones::IndicesByteSize::UNSIGNED_BYTE;
	else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) byteSize = Bones::IndicesByteSize::UNSIGNED_SHORT;
	else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) byteSize = Bones::IndicesByteSize::UNSIGNED_INT;

	// check if in cache and return index.
	int index = 0;
	for (; index < cache.size(); index++)
	{
		auto& cacheEntry = cache.at(index);
		if (cacheEntry.m_indicesIndex == primitive.indices && cacheEntry.m_structComponentLength == byteSize)
			return index;
	}

	// Create indices
	Indices indicesData;
	indicesData.indicesByteSize = byteSize;
	indicesData.indices.reserve(bufferView.byteLength * bufferView.byteOffset);
	for (size_t i = bufferView.byteOffset; i < bufferView.byteLength + bufferView.byteOffset; i++)
	{
		indicesData.indices.push_back(buffer.data.at(i));
	}

	// Add to model data and to cache.
	modelData.indicesBuffersData.push_back(indicesData);
	cache.push_back({ index, byteSize, indicesData });
	return index;
}

void TinyGltfLoader::LoadModel(const string& filename, ModelData& modelData, OptionsBitField options)
{
	int normalFlip = (options & MODEL_LOADER_FLIP_NORMALS) ? -1 : 1;
	float textureFlip = (options & MODEL_LOADER_FLIP_TEX_COORDS_Y) ? 1.0f : 0.0f;
	int textureFlipMul = (options & MODEL_LOADER_FLIP_TEX_COORDS_Y) ? -1 : 1;

	std::string warn;
	std::string err;

	tinygltf::Model tinyModel;
	auto path = filename.substr(0, filename.find_last_of("\\/"));
	tinygltf::TinyGLTF loader;


	// Check if binary and load properly.
	bool isBinary = filename.substr(filename.find_last_of('.')) == ".glb";
	bool result = false;

	// if binary try to load it.
	if (isBinary)
	{
		result = loader.LoadBinaryFromFile(&tinyModel, &err, &warn, filename.c_str());
	}
	else 
	{
		result = loader.LoadASCIIFromFile(&tinyModel, &err, &warn, filename.c_str());
	}

	// wrong format.
	if (!result)
	{
		if (isBinary)
		{
			std::cout << "Binary load failed. Attempting to load '" << filename << "' as JSON ASCII." << std::endl;
			result = loader.LoadASCIIFromFile(&tinyModel, &err, &warn, filename.c_str());
		}
		else
		{
			std::cout << "ASCII JSON load failed. Attempting to load '" << filename << "' as binary." << std::endl;
			result = loader.LoadBinaryFromFile(&tinyModel, &err, &warn, filename.c_str());
		}
	}

	ASSERT(result)

	if (!warn.empty())
	{
		std::cout << warn << std::endl;
	}

	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}

	if (!result)
	{
		return;
	}

	// Temporary cache of indices reference by index as it comes fron tiny loader, 
	// then by indices size then indices buffer is retrieved. 
	std::vector<TinyGltfLoader::CacheMap> cache;

	vector<tinygltf::Material>& materials = tinyModel.materials;
	vector<tinygltf::Mesh>& meshes = tinyModel.meshes;

	modelData.materials.reserve(materials.size());
	modelData.meshes.reserve(meshes.size());

	for (size_t i = 0; i < materials.size(); i++)
	{
		auto& matData = materials[i];
		MaterialData material;

		/*if (matData.diffuse_texname != "")
		{
			material.diffuse = { matData.diffuse_texname };
		}*/

		modelData.materials.emplace_back(material);
	}

	LOG_FORMAT("%s", filename.c_str());
	// Loop over meshes
	for (size_t m = 0; m < meshes.size(); m++) {

		// Loop over faces(polygon)
		size_t index_offset = 0;
		tinygltf::Primitive& primitive = meshes[m].primitives[0];

		MeshData mesh;

		// handle indicies

		if (primitive.indices >= 0)
		{
			mesh.drawMode = DrawMode::ELEMENTS;
			mesh.indicesIndex = FindIndicesBufferIndex(cache, tinyModel, primitive, modelData);
		}

		// handle positions
		if (primitive.attributes.count("POSITION") > 0)
		{
			// Get position accessor index
			int accessorIndex = primitive.attributes.at("POSITION");
			tinygltf::Accessor& accessor = tinyModel.accessors.at(accessorIndex);

			// get buffer and buffer view 
			tinygltf::BufferView& bufferView = tinyModel.bufferViews.at(accessor.bufferView);
			tinygltf::Buffer& buffer = tinyModel.buffers.at(bufferView.buffer);

			// for example float, vec2, vec3 ...
			int componentSize = 0;
			// size of bytes as sizeof(float), sizeof(uint) etc...
			int byteSize = 0;

			if (primitive.mode == TINYGLTF_MODE_TRIANGLES) mesh.drawType = DrawType::TRIANGLES;
			else if (primitive.mode == TINYGLTF_MODE_LINE) mesh.drawType = DrawType::LINES;

			if (accessor.type == TINYGLTF_TYPE_SCALAR) componentSize = 1;
			else if (accessor.type == TINYGLTF_TYPE_VEC2) componentSize = 2;
			else if (accessor.type == TINYGLTF_TYPE_VEC3) componentSize = 3;
			else if (accessor.type == TINYGLTF_TYPE_VEC4) componentSize = 4;

			if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) byteSize = sizeof(float);

			// length  / sizeof()
			int reserve = static_cast<int>(bufferView.byteLength) / byteSize;
			mesh.vertices.reserve(reserve);

			std::vector<unsigned char>& data = tinyModel.buffers[bufferView.buffer].data;

			for (size_t i = bufferView.byteOffset; i < bufferView.byteLength + bufferView.byteOffset; i += byteSize)
			{

				if (byteSize == 4)
				{
					float f = 0.0f;
					memcpy(&f, &data[i], sizeof(float));
					mesh.vertices.push_back(f);
				}
			}
		}


		modelData.meshes.emplace_back(mesh);


		/*MeshData mesh;
		mesh.vertices.reserve(size * 3);
		mesh.normals.reserve(size * 3);
		mesh.texCoords.reserve(size * 3);
		mesh.indices.reserve(size);*/

		/*auto index = shapes[s].material_ids[size - 1];
		mesh.materialIndex = index < 0 ? 0 : index;*/

		//for (size_t f = 0; f < size; f++) {
		//	int fv = shapes[s].mesh.num_face_vertices[f];

		//	// Loop over vertices in the face.
		//	for (size_t v = 0; v < fv; v++) {
		//		// access to vertex
		//		tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
		//		tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
		//		tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
		//		tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
		//		tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0] * normalFlip;
		//		tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1] * normalFlip;
		//		tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2] * normalFlip;
		//		tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
		//		tinyobj::real_t ty = textureFlip + attrib.texcoords[2 * idx.texcoord_index + 1] * textureFlipMul;
		//		// Optional: vertex colors
		//		// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
		//		// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
		//		// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

		//		mesh.vertices.emplace_back(vx);
		//		mesh.vertices.emplace_back(vy);
		//		mesh.vertices.emplace_back(vz);

		//		mesh.normals.emplace_back(nx);
		//		mesh.normals.emplace_back(ny);
		//		mesh.normals.emplace_back(nz);

		//		mesh.texCoords.emplace_back(tx);
		//		mesh.texCoords.emplace_back(ty);

		//		mesh.indices.emplace_back(index_offset + v);
		//	}
		//	index_offset += fv;
		//}

		// data.meshes.emplace_back(mesh);
	}
}

ModelData TinyGltfLoader::LoadModel(const string& filename, OptionsBitField options)
{
	ModelData model;
	LoadModel(filename, model, options);
	return model;
}



#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;
using namespace Bones;
using namespace Bones::Vendor;

EMSCRIPTEN_BINDINGS(TinyGltfLoader_JS)
{
	//class_<TinyObjLoader, base<BaseModelLoader>>("TinyObjLoader")
	//	.constructor()
	//	.function("LoadModel", select_overload<ModelData(const string&, OptionsBitField)>(&TinyObjLoader::LoadModel), allow_raw_pointers());
}

#endif