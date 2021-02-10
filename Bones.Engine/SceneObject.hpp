#pragma once

#ifndef SCENEOBJECT_H

#define SCENEOBJECT_H

#include "TransformComponent.hpp"
#include "DrawOutlineComponent.hpp"
#include "ShaderManager.hpp"
#include <vector>
#include <string>

using namespace Bones::Component;
using Bones::Managers::ShaderManager;
using Bones::Components::Draw::DrawOutlineComponent;

namespace Bones
{
	class Scene;

	namespace Mesh
	{
		class BaseMesh;
	}
}

using std::vector;
using Bones::Scene;
using namespace Bones::Mesh;

/// <summary>
/// Scene object which contains meshes of object, other objects and various other components.
/// </summary>
class SceneObject
{
private:
	static unsigned long id;
	bool m_initialized = false;
	vector<BaseMesh*> m_meshes;
	
public:
	bool m_active = true;
	std::string m_name;
	// TODO: this is quick fix to render opaque objects first.
	bool m_hasTransparency = false;

	Scene* m_scene = nullptr;
	TransformComponent* m_transform = nullptr;
	DrawOutlineComponent* m_drawOutline = nullptr;

	SceneObject(Scene* scene, vector<BaseMesh*> meshes, std::string name = "");
	SceneObject(Scene* scene, BaseMesh* mesh, std::string name = "");
	SceneObject(Scene* scene);
	~SceneObject();

	// getters 
	const vector<BaseMesh*>& GetMeshes() { return m_meshes; } 
    TransformComponent& GetTransform() { return *m_transform; }

	void AddMesh(BaseMesh* mesh);
	void Initialize();

	void UseDrawOutline(bool useDrawOutline, glm::vec4 outlineColor = glm::vec4(0.7, 0.3, 1, 0.8), float scale = 1.075f);
	
};

#endif // !SCENEOBJECT_H