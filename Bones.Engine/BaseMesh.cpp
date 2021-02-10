#include "BaseMesh.hpp"
#include "BaseGeometry.hpp"
#include "BaseMaterial.hpp"
#include "SceneObject.hpp"


BaseMesh::BaseMesh(BaseGeometry* geometry, BaseMaterial* material)
	: m_geometry(geometry), m_material(material), m_sceneObjectParent(nullptr) 
{
	m_state = State::New;
}


BaseMesh::~BaseMesh()
{
	if (m_state != State::Destroyed)
	{
		m_state = State::Destroyed;

		m_geometry = nullptr;

		m_material = nullptr;

		// just clear pointer. Not responsible for deleting parent objects.
		m_sceneObjectParent = nullptr;
	}
}

void BaseMesh::AttachToParent(SceneObject& sceneObject)
{
	m_sceneObjectParent = &sceneObject;
	sceneObject.AddMesh(this);
}

void BaseMesh::Initialize()
{
	m_state = State::Initialized;
	m_material->Initialize();
	m_geometry->InitializeBuffers(m_material->GetShader().GetProgram());
}

void BaseMesh::UseMesh()
{
	m_material->UseMaterial();
}


void BaseMesh::Render()
{
	// bind buffers, glDraw, unbind buffers

	m_geometry->Draw();
}
