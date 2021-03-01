#include "MeshManager.hpp"
#include "StandardMaterial.hpp"
#include "BaseGeometry.hpp"
#include "StandardMaterialMesh.hpp"
#include "DELETE_MACROS.h"

using Bones::Managers::MeshManager;

vector<StandardMaterialMesh*> MeshManager::m_meshes;
State MeshManager::m_state = State::New;

StandardMaterialMesh* MeshManager::CreateStandardMaterialMesh(BaseGeometry* geometry, StandardMaterial* material)
{
	StandardMaterialMesh* ptr = new StandardMaterialMesh(geometry, material);
	m_meshes.push_back(ptr);
	return ptr;
}

void MeshManager::Destroy(StandardMaterialMesh* mesh)
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		if (m_meshes[i] == mesh)
		{
			m_meshes.erase(m_meshes.begin() + i);
			break;
		}
	}

	delete mesh;
}

void MeshManager::Destroy()
{
	DELETE_VECTOR(MeshManager::m_meshes);
	m_state = State::Destroyed;
}
