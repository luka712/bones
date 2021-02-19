#include "Skybox.hpp"
#include "GeometryManager.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "EnvironmentMapGeometry.hpp"
#include "BaseCamera.hpp"
#include "CubeTexture.hpp"

using Bones::Environment::Skybox;
using Bones::Managers::TextureManager; 
using Bones::Managers::GeometryManager;
using Bones::Managers::ShaderManager;
using Bones::Camera::BaseCamera;


Skybox::Skybox(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back)
{
	LOG_CONSTRUCTOR();
	str[0] = right;
	str[1] = left;
	str[2] = top;
	str[3] = bottom;
	str[4] = front;
	str[5] = back;
}

void Skybox::Load()
{
	LOG_LOAD();
	m_state = State::Loaded;
	m_texture = TextureManager::GetOrCreateCubeTexture(str[0], str[1], str[2], str[3], str[4], str[5]);
}

void Skybox::Initialize()
{
	LOG_INITIALIZE();
	m_state = State::Initialized;
	m_geometry = GeometryManager::GetOrCreateEnvironmentMapGeometry();
	m_shader = ShaderManager::GetOrCreateSkyboxShader();
}

void Skybox::Draw(const BaseCamera& camera)
{
	// must be less or equal function, since env map is drawn on z = 1 ( which is furthest away possible )
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	m_shader->UseProgram();
	m_shader->SetCameraLocations(camera);
	m_shader->SetInt(m_shader->m_cubeTextureLocation, 0);
	m_texture->BindTexture();
	m_geometry->Draw();
}


Skybox::~Skybox()
{
	LOG_DESTRUCTOR();
	m_state = State::Destroyed;
	TextureManager::DeleteCubeTexture(m_texture);
	m_texture = nullptr;

	m_geometry = nullptr;
}