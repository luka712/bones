// https://github.com/tinyobjloader/tinyobjloader
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "TinyObjLoader.hpp"


void Bones::Vendor::TinyObjLoader::LoadModel(const string& filename, ModelData& data, OptionsBitField options)
{
	int normalFlip = (options & MODEL_LOADER_FLIP_NORMALS) ? -1 : 1;
	float textureFlip = (options & MODEL_LOADER_FLIP_TEX_COORDS_Y) ? 1.0f : 0.0f;
	int textureFlipMul = (options & MODEL_LOADER_FLIP_TEX_COORDS_Y) ? -1 : 1;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto path = filename.substr(0, filename.find_last_of("\\/"));
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), path.c_str(), false);

	if (!warn.empty())
	{
		std::cout << warn << std::endl;
	}

	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}

	if (!ret)
	{
		return;
	}

	data.materials.reserve(materials.size());
	data.meshes.reserve(shapes.size());

	for (size_t i = 0; i < materials.size(); i++)
	{
		auto& matData = materials[i];
		MaterialData material;
	
		if (matData.diffuse_texname != "")
		{
			material.diffuse = { matData.diffuse_texname };
		}

		data.materials.emplace_back(material);
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		size_t size = shapes[s].mesh.num_face_vertices.size();

		MeshData mesh;
		mesh.vertices.reserve(size * 3);
		mesh.normals.reserve(size * 3);
		mesh.texCoords.reserve(size * 3);
		mesh.indices.reserve(size);
	
		auto index = shapes[s].mesh.material_ids[size - 1];
		mesh.materialIndex = index < 0 ? 0 : index;

		for (size_t f = 0; f < size; f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0] * normalFlip;
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1] * normalFlip;
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2] * normalFlip;
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = textureFlip + attrib.texcoords[2 * idx.texcoord_index + 1] * textureFlipMul;
				// Optional: vertex colors
				// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

				mesh.vertices.emplace_back(vx);
				mesh.vertices.emplace_back(vy);
				mesh.vertices.emplace_back(vz);

				mesh.normals.emplace_back(nx);
				mesh.normals.emplace_back(ny);
				mesh.normals.emplace_back(nz);

				mesh.texCoords.emplace_back(tx);
				mesh.texCoords.emplace_back(ty);

				mesh.indices.emplace_back(index_offset + v);
			}
			index_offset += fv;
		}

		data.meshes.emplace_back(mesh);
	}
}

ModelData Bones::Vendor::TinyObjLoader::LoadModel(const string& filename, OptionsBitField options)
{
	ModelData model;
	LoadModel(filename, model, options);
	return model;
}



#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;
using namespace Bones;
using namespace Bones::Vendor;

EMSCRIPTEN_BINDINGS(TinyObjLoader_JS)
{
	class_<TinyObjLoader, base<BaseModelLoader>>("TinyObjLoader")
		.constructor()
		.function("LoadModel", select_overload<ModelData(const string&, OptionsBitField)>(&TinyObjLoader::LoadModel), allow_raw_pointers());
}

#endif