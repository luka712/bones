#pragma once

#ifndef SCENE_H

#define SCENE_H

#include <algorithm>
#include <functional>
#include "FreeCamera.hpp"
#include "OrbitCamera.hpp"
#include "SceneObject.hpp"
#include "DirectionalLight.hpp"
#include "FreeCamera.hpp"
#include "SpotLight.hpp"
#include "BaseMaterial.hpp"
#include "Constants.hpp"


namespace Bones
{
	namespace PostProcessPipeline
	{
		class BasePostProcessPipeline;
	}

	namespace Lights
	{
		class AmbientLight;
	}

	namespace Environment
	{
		class Skybox;
	}
}

using namespace Bones::Camera;
using namespace Bones::Lights;
using Bones::Environment::Skybox;
using Bones::Materials::BaseMaterial;

using Bones::PostProcessPipeline::BasePostProcessPipeline;
using Bones::State;

using std::function;

namespace Bones
{
	class Scene
	{
	private:
		vector<BaseMaterial*> m_materials;

		unsigned int m_activeCameraIndex = 0;
		vector<BaseCamera*> m_cameras;

#pragma region EVENTS
		vector<function<void(SceneObject&)>> m_sceneObjectAddedEvents;
#pragma endregion

	public:
		vector<DirectionalLight*> m_directionalLights;
		vector<PointLight*> m_pointLights;
		vector<SpotLight*> m_spotLights;

		State m_state = State::New;
		string m_name;
		Skybox* m_skybox;
		AmbientLight* m_ambientLight;

		BasePostProcessPipeline* m_postProcessPipeline = nullptr;
		vector<SceneObject*> m_sceneObjects;

		Scene(const string name);
		Scene(const string name, BaseCamera* camera);
		~Scene();

		void Load();
		void Initialize();

		const string& GetName() const noexcept { return m_name; }
		const vector<SceneObject*>& GetObjects() const { return m_sceneObjects; }

		BaseCamera& GetActiveCamera() const { return *m_cameras[m_activeCameraIndex]; }

		const vector<DirectionalLight*>& GetDirectionalLights() { return m_directionalLights; }
		const vector<PointLight* >& GetPointLights() const noexcept { return m_pointLights; }
		const vector<SpotLight* >& GetSpotLights() const noexcept { return m_spotLights; }

		// Skybox or environment map
		void SetSkybox(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back);
		void UseDefaultSkybox();
		void UseCupertinSkybox();
		void DisableSkybox();


		void AddMaterial(BaseMaterial* material);

		void SetAmbientLight(AmbientLight* ambientLight);

		void AddDirectionalLight(DirectionalLight* directionalLight);
		void AddPointLight(PointLight* pointLight);
		void AddSpotLight(SpotLight* spotLight);

		void AddCamera(BaseCamera* camera);

		/// <summary>
		/// Adds new scene object to scene.
		/// </summary>
		void AddSceneObject(SceneObject* object);
		/// <summary>
		/// Fired when scene object is added to scene.
		/// </summary>
		void OnSceneObjectAdded(function<void(SceneObject& obj)> cb);
	};
}

#endif // !SCENE_H