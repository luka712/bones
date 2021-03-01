#pragma once

#ifndef BASE_MODEL_LOADER

#define BASE_MODEL_LOADER


#include <string>
#include <iostream>
#include <vector>
#include "core_types.h"
#include "sdl_include.h"

using namespace std;

namespace Bones
{
	namespace Loaders
	{
		struct Indices
		{
			vector<U8> indices;
			IndicesByteSize indicesByteSize = IndicesByteSize::NONE;
		};

		struct MeshData
		{
			DrawMode drawMode = DrawMode::ARRAYS;
			DrawType drawType = DrawType::TRIANGLES;
			vector<F32> vertices;
			vector<F32> texCoords;
			vector<F32> normals;
			vector<U32> indices;

			// if -1 indices are not created. Else it's ref to indicesBufferData of ModelData.
			I32 indicesIndex = -1;

			I64 materialIndex = -1;
		};

		struct ModelTextureData
		{
			string textureName;
		};

		struct MaterialData
		{
			ModelTextureData diffuse;
		};

		struct ModelData
		{
			// All the buffers for indices
			vector<Indices> indicesBuffersData;

			vector<MeshData> meshes;
			vector<MaterialData> materials;
		};

		typedef unsigned int OptionsBitField;

#define MODEL_LOADER_FLIP_TEX_COORDS_Y 0b00000001
#define MODEL_LOADER_FLIP_NORMALS 0b00000010

		class BaseModelLoader
		{
		public:
			virtual void LoadModel(const string& filename, ModelData& data, OptionsBitField options = 0) = 0;
			virtual ModelData LoadModel(const string& filename, OptionsBitField options = 0) = 0;
			~BaseModelLoader();
		};
	}

}


#endif // !BASE_MODEL_LOADER