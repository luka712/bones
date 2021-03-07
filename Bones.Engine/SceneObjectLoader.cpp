#include <vector>
#include "TinyObjLoader.hpp"
#include "BlyObjLoader.hpp"
#include "TinyGltfLoader.hpp"
#include "SceneObject.hpp"
#include "SceneObjectLoader.hpp"
#include "StandardMaterialMesh.hpp"
#include "TextureManager.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "MaterialManager.hpp"
#include "BaseGeometry.hpp"
#include "Scene.hpp"
#include "MaterialManager.hpp"
#include "MeshManager.hpp"
#include "BuffersManager.hpp"
#include "StandardMaterial.hpp"

using Bones::Scene;
using Bones::DrawMode;
using Bones::DrawType;

using Bones::Vendor::TinyObjLoader;
using Bones::Vendor::BlyObjLoader;
using Bones::Vendor::TinyGltfLoader;

using namespace Bones::Managers;

using Bones::Buffers::VertexBuffer;
using Bones::Buffers::IndexBuffer;
using Bones::Materials::StandardMaterial;
using Bones::Mesh::StandardMaterialMesh;

using Bones::Geometry::BaseGeometry;

vector<SceneObject*> SceneObjectLoader::LoadFromObjFile(Scene& scene, const string& path)
{
	BlyObjLoader loader;
	ModelData modelData = loader.LoadModel(path, MODEL_LOADER_FLIP_TEX_COORDS_Y);
	// ModelData modelData = loader.LoadModel(path);
	vector<StandardMaterial*> materials;
	size_t idx = string(path).rfind("/");
	string filepath = string(path).substr(0, idx + 1);
	string filename = string(path).substr(idx + 1);

	for (int i = 0; i < modelData.materials.size(); i++)
	{
		StandardMaterialOptions opts{};
		MaterialData& materialData = modelData.materials[i];

		// find file name
		ModelTextureData& diffuse = materialData.diffuse;
		Texture2D* diffuseTexture = nullptr;
		if (materialData.diffuse.textureName != "")
		{
			size_t idx = string(diffuse.textureName).rfind("\\");
			string filename = string(diffuse.textureName).substr(idx + 1);

			diffuseTexture = TextureManager::GetOrCreateTexture2D(filepath + filename);
			opts.useDiffuseMap = true;
		}

		StandardMaterial* material = MaterialManager::CreateStandardMaterial(filename + "_" + to_string(i), opts);
		material->m_specularShininess = 32;
		if (diffuseTexture)
		{
			material->SetDiffuseTexture(diffuseTexture);
		}

		materials.push_back(material);
	}

	vector<BaseMesh*> meshes;
	SceneObject* scnObj = nullptr;
	for (int i = 0; i < modelData.meshes.size(); i++)
	{
		MeshData& aMesh = modelData.meshes[i];
		VertexBuffer* vBuffer = BuffersManager::CreateVertexBuffer(0, 3, aMesh.vertices.data(), aMesh.vertices.size());
		VertexBuffer* tBuffer = BuffersManager::CreateVertexBuffer(1, 2, aMesh.texCoords.data(), aMesh.texCoords.size());
		VertexBuffer* nBuffer = BuffersManager::CreateVertexBuffer(2, 3, aMesh.normals.data(), aMesh.normals.size());
		IndexBuffer* iBuffer = BuffersManager::CreateIndexBuffer(aMesh.indices.data(), static_cast<int>(aMesh.indices.size()));

		BaseGeometry* geometry = new BaseGeometry(vBuffer, tBuffer, nBuffer, iBuffer);

		StandardMaterial* material = nullptr;
		if (materials.size() > 0)
		{
			material = materials[aMesh.materialIndex];
		}
		else
		{
			material = MaterialManager::CreateStandardMaterial(filename + "_" + to_string(i), 0);
		}

		meshes.push_back(MeshManager::CreateStandardMaterialMesh(geometry, material));
	}

	scnObj = new SceneObject(&scene, meshes);
	scnObj->m_name = filename;
	scene.AddSceneObject(scnObj);


	return vector<SceneObject*> {scnObj };
}


vector<SceneObject*> SceneObjectLoader::LoadFromGltfFile(Scene& scene, const string& path)
{
	TinyGltfLoader loader;
	ModelData modelData = loader.LoadModel(path, MODEL_LOADER_FLIP_TEX_COORDS_Y);
	// ModelData modelData = loader.LoadModel(path);
	vector<StandardMaterial*> materials;
	size_t idx = string(path).rfind("/");
	string filepath = string(path).substr(0, idx + 1);
	string filename = string(path).substr(idx + 1);

	for (size_t i = 0; i < modelData.materials.size(); i++)
	{
		StandardMaterialOptions opts{};
		MaterialData& materialData = modelData.materials[i];

		// find file name
		ModelTextureData& diffuse = materialData.diffuse;
		Texture2D* diffuseTexture = nullptr;
		if (materialData.diffuse.textureName != "")
		{
			size_t idx = string(diffuse.textureName).rfind("\\");
			string filename = string(diffuse.textureName).substr(idx + 1);

			diffuseTexture = TextureManager::GetOrCreateTexture2D(filepath + filename);
			opts.useDiffuseMap = true;
		}

		StandardMaterial* material = MaterialManager::CreateStandardMaterial(filename + "_" + to_string(i), opts);
		material->m_specularShininess = 32;
		if (diffuseTexture)
		{
			material->SetDiffuseTexture(diffuseTexture);
		}

		materials.push_back(material);
	}

	vector<BaseMesh*> meshes;
	SceneObject* scnObj = nullptr;

	// Insert to indices 
	std::vector<IndexBuffer*> indexBuffers;
	for (auto& iData : modelData.indicesBuffersData)
	{
		indexBuffers.push_back(  BuffersManager::CreateIndexBuffer(iData.indices.data(), static_cast<I32>(iData.indices.size()), iData.indicesByteSize));
	}

	// TODO: insert to various vertices

	for (size_t i = 0; i < modelData.meshes.size(); i++)
	{
		MeshData& aMesh = modelData.meshes[i];
		BaseGeometry* geometry = nullptr;
		if (aMesh.drawMode == DrawMode::ARRAYS)
		{
			// TODO: through geometry manager.
			VertexBuffer* posVBuffer = BuffersManager::CreateVertexBuffer(0, 3, aMesh.vertices.data(), aMesh.vertices.size());
			geometry = new BaseGeometry(posVBuffer, aMesh.vertices.size() / 3, aMesh.drawType);
		}
		else
		{
			if (aMesh.texCoords.size() == 0 && aMesh.normals.size() == 0)
			{
				// TODO: through geometry manager.
				VertexBuffer* posVBuffer = BuffersManager::CreateVertexBuffer(0, 3, aMesh.vertices.data(), aMesh.vertices.size());
				geometry = new BaseGeometry(posVBuffer,indexBuffers[aMesh.indicesIndex], aMesh.drawType);
			}
			else
			{
				// TODO: through geometry manager.
				VertexBuffer* posVBuffer = BuffersManager::CreateVertexBuffer(0, 3, aMesh.vertices.data(), aMesh.vertices.size());
				VertexBuffer* texCoordVBuffer = BuffersManager::CreateVertexBuffer(1, 2, aMesh.texCoords.data(), aMesh.texCoords.size());
				VertexBuffer* normalsVBuffer = BuffersManager::CreateVertexBuffer(2, 3, aMesh.normals.data(), aMesh.normals.size());

				geometry = new BaseGeometry(posVBuffer, texCoordVBuffer, normalsVBuffer,indexBuffers[aMesh.indicesIndex]);
			}
		}

		StandardMaterial* material = nullptr;
		/*	if (materials.size() > 0)
			{
				material = materials[aMesh.materialIndex];
			}
			else
			{*/
		material = MaterialManager::CreateStandardMaterial(filename + "_" + to_string(i), 0);
		//}

		meshes.push_back(MeshManager::CreateStandardMaterialMesh(geometry, material));
	}

	scnObj = new SceneObject(&scene, meshes, filename);
	scene.AddSceneObject(scnObj);

	return vector<SceneObject*> {scnObj };
}
