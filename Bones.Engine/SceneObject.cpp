#include "SceneObject.hpp"
#include "StandardMaterialMesh.hpp"
#include "Scene.hpp"
#include <vector>

using std::vector;
using Bones::Scene;

unsigned long SceneObject::id = 0;

SceneObject::SceneObject(Scene* scene, vector<BaseMesh*> meshes, std::string name)
{
	SceneObject::id++;
	m_name = name;
	m_scene = scene;
	m_transform = new TransformComponent();
	for (BaseMesh* mesh : meshes)
	{
		AddMesh(mesh);
	}
}

SceneObject::SceneObject(Scene* scene, BaseMesh* mesh, std::string name)
	:SceneObject(scene, vector<BaseMesh*> { mesh }, name)
{
}

SceneObject::SceneObject(Scene* scene)
	: SceneObject(scene, vector<BaseMesh*> {})
{
}

void SceneObject::AddMesh(BaseMesh* mesh)
{
	// find an element. If not found add.
	if (find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end())
	{
		m_meshes.push_back(mesh);
		mesh->AttachToParent(*this);
	}
#ifdef DEBUG
	else
	{
		cout << "Mesh already belongs to object." << endl;
	}
#endif
}

void SceneObject::Initialize()
{
	if (m_initialized) return;

	m_initialized = true;
	for (BaseMesh* mesh : m_meshes)
	{
		mesh->Initialize();
	}

	if (m_drawOutline != nullptr)
	{
		m_drawOutline->Initialize();
	}
}

void SceneObject::UseDrawOutline(bool useDrawOutline, glm::vec4 outlineColor, float scale)
{
	if (useDrawOutline)
	{
		m_drawOutline = new DrawOutlineComponent(this);
		m_drawOutline->m_color = outlineColor;
		m_drawOutline->m_scaleFactor = scale;
		m_drawOutline->Initialize();
	}
	else
	{
		delete m_drawOutline;
		m_drawOutline = nullptr;
	}
}


SceneObject::~SceneObject()
{
	DELETE_PTR(m_transform);
	DELETE_PTR(m_drawOutline);

	m_meshes.clear();

}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(SceneObject_JS)
{/*
	class_<SceneObject>("SceneObject")
		.constructor()
		.function("GetTransform", optional_override([](SceneObject& self) -> TransformComponent* { return &self.GetTransform(); }), allow_raw_pointers());*/
}

#endif