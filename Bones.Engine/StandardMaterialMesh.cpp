#include "StandardMaterialMesh.hpp"
#include "MaterialShaderStructs.hpp"
#include "SceneObject.hpp"
#include "MaterialShader.hpp"
#include "MaterialManager.hpp"
#include "StandardMaterial.hpp"
#include "BaseGeometry.hpp"
#include "core_types.h"

using Bones::Mesh::StandardMaterialMesh;
using Bones::Shaders::Material::MaterialLocations;
using Bones::Managers::MaterialManager;

StandardMaterialMesh::StandardMaterialMesh(BaseGeometry* geometry, StandardMaterial* material)
	: BaseMesh(geometry, material)
{
	m_sceneObjectParent = nullptr;
	m_material = material;
}

StandardMaterialMesh::~StandardMaterialMesh()
{
	// removed from parent.
	m_material = nullptr;
}

void StandardMaterialMesh::UseMesh()
{
	const MaterialShader& shader = *m_material->m_shader;
	const MaterialLocations& materialLocations = shader.m_materialLocations;

	// setup uniform specific to mesh.
	m_sceneObjectParent->GetTransform().UseTransform(shader.m_transformLocation);

	// setup material uniforms specific to mesh.
	m_material->UseMaterial();
}

void StandardMaterialMesh::Render()
{
#if EMSCRIPTEN == 0
	glPolygonMode(GL_FRONT_AND_BACK, m_material->GetPolygonMode());
#endif 
	BaseMesh::Render();
}
