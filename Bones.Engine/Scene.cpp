#include "Scene.hpp"
#include "BaseMaterial.hpp"
#include "AmbientLight.hpp"
#include "BasePostProcessPipeline.hpp"
#include "Skybox.hpp"

using Bones::Materials::BaseMaterial;
using namespace Bones::Camera;

using Bones::Scene;

// using Bones::PostProcessPipeline::BasePostProcessPipeline;

Scene::Scene(const string name)
	: Scene(name, new OrbitCamera())
{
}

Scene::Scene(const string name, BaseCamera* camera)
	: m_name(name)
{
	m_postProcessPipeline = new BasePostProcessPipeline();
	AddCamera(camera);

	// default ambient light 
	m_ambientLight = new AmbientLight();

	// default directional light 
	m_directionalLights.reserve(MAX_DIRECTIONAL_LIGHTS);
	//  AddDirectionalLight(new DirectionalLight());
	m_pointLights.reserve(MAX_POINT_LIGHTS);
	m_spotLights.reserve(MAX_SPOT_LIGHTS);
}

Scene::~Scene()
{
	for (BaseCamera* camera : m_cameras)
	{
		delete camera;
	}
	m_cameras.clear();

	for (SceneObject* sceneObj : m_sceneObjects)
	{
		delete sceneObj;
	}
	m_sceneObjects.clear();

	if (m_ambientLight)
	{
		delete m_ambientLight;
		m_ambientLight = nullptr;
	}

	for (DirectionalLight* dirLight : m_directionalLights)
	{
		delete dirLight;
	}
	m_directionalLights.clear();

	for (PointLight* pointLight : m_pointLights)
	{
		delete pointLight;
	}
	m_pointLights.clear();

	for (SpotLight* spotLight : m_spotLights)
	{
		delete spotLight;
	}
	m_spotLights.clear();

	delete m_postProcessPipeline;
	m_postProcessPipeline = nullptr;
}

void Scene::Load()
{
	if (m_state == State::New)
	{
		LOG_FORMAT("Scene %s already loaded.", m_name.c_str());
		return;
	}

	if (m_skybox != nullptr) m_skybox->Load();

	m_state = State::Loaded;
}

void Scene::Initialize()
{
	if (m_state == State::Loaded)
	{
		LOG_FORMAT("Scene %s already initialized.", m_name.c_str());
		return;
	}

	if (m_skybox != nullptr) m_skybox->Initialize();

	m_state = State::Initialized;
}

void Scene::SetSkybox(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back)
{
	if (m_skybox != nullptr)
	{
		delete m_skybox;
	}
	m_skybox = new Skybox(right, left, top, bottom, front, back);
	if (m_state >= State::Loaded) m_skybox->Load();
	if (m_state >= State::Initialized) m_skybox->Initialize();
}

void Scene::UseDefaultSkybox()
{
	string path = "resources/textures/environment/skybox/";
	SetSkybox(path + "right.jpg", path + "left.jpg", path + "top.jpg", path + "bottom.jpg", path + "front.jpg", path + "back.jpg");
}

void Scene::DisableSkybox()
{
	this->m_skybox = nullptr;
	delete m_skybox;
}

void Scene::UseCupertinSkybox()
{
	string path = "resources/textures/environment/cupertin/";
	SetSkybox(path + "right.tga", path + "left.tga", path + "top.tga", path + "bottom.tga", path + "front.tga", path + "back.tga");
}


void Scene::AddMaterial(BaseMaterial* material)
{
	if (material != nullptr)
	{
		bool isDupeName = any_of(m_materials.begin(), m_materials.end(), [&](BaseMaterial* x) { return x->GetName() == material->GetName(); });
		if (!isDupeName)
		{
			m_materials.push_back(material);
			material->Initialize();
		}
		else
		{
			cout << "Cannot add shader " << material->GetName() << ". Shader with same name already added." << endl;
		}
	}
}

void Scene::SetAmbientLight(AmbientLight* light)
{
	if (light)
		light->Initialize();

	m_ambientLight = light;
}

void Scene::AddDirectionalLight(DirectionalLight* directionalLight)
{
	if (m_directionalLights.size() < MAX_DIRECTIONAL_LIGHTS)
	{
		directionalLight->Initialize();
		m_directionalLights.push_back(directionalLight);
	}
	else
	{
		cout << "Unable to add directional light. Maximum point lights count reached." << endl;
	}
}

void Scene::AddPointLight(PointLight* pointLight)
{
	if (m_pointLights.size() < MAX_POINT_LIGHTS)
	{
		pointLight->Initialize();
		m_pointLights.push_back(pointLight);
	}
	else
	{
		cout << "Unable to add point light. Maximum point lights count reached." << endl;
	}
}

void Scene::AddSpotLight(SpotLight* spotLight)
{
	if (m_spotLights.size() < MAX_SPOT_LIGHTS)
	{
		spotLight->Initialize();
		m_spotLights.push_back(spotLight);
	}
	else
	{
		cout << "Unable to add point light. Maximum spot lights count reached." << endl;
	}
}

void Scene::AddCamera(BaseCamera* camera)
{
	m_cameras.emplace_back(camera);
}

void Scene::AddSceneObject(SceneObject* sceneObject) 
{
	m_sceneObjects.emplace_back(sceneObject);
	sceneObject->Initialize();

	// fire events
	for(auto& cb: m_sceneObjectAddedEvents)
		cb(*sceneObject);
}

void Scene::OnSceneObjectAdded(function<void(SceneObject& obj)> cb)
{
	m_sceneObjectAddedEvents.push_back(cb);
}


#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(Scene_JS)
{
	class_<Scene>("Scene")
		.function("GetPostProcessPipeline", optional_override([](Scene& scene) { return scene.m_postProcessPipeline; }), allow_raw_pointers())
		.function("UseDefaultSkybox", &Scene::UseDefaultSkybox)
		.function("UseCupertinSkybox", &Scene::UseCupertinSkybox)
		.function("DisableSkybox", &Scene::DisableSkybox);

}

#endif