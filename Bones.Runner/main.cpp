#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "Engine.hpp"
#include "Scene.hpp"
#include "StandardMaterial.hpp"
#include "StandardMaterialMesh.hpp"
#include "SceneObjectLoader.hpp"
#include "BasePostProcessPipeline.hpp"
#include "MaterialManager.hpp"
#include "SceneManager.hpp"
#include "MeshManager.hpp"
#include "SceneObject.hpp"
#include "GeometryManager.hpp"
#include "BoxGeometry.hpp"
#include "QuadGeometry.hpp"
#include "PostProcessFramebuffer.hpp"
#include "BasePostProcessShader.hpp"
#include "TextureManager.hpp"
#include "NightVisionPostProcessFramebuffer.hpp"
#include "UIManager.hpp"

using Bones::Engine;
using Bones::Scene;
using Bones::Materials::StandardMaterial;
using Bones::Managers::MaterialManager;
using Bones::Managers::SceneManager;
using Bones::Managers::GeometryManager;
using Bones::Managers::MeshManager;
using Bones::Managers::TextureManager;
using Bones::Loaders::SceneObjectLoader;
using Bones::PostProcessPipeline::BasePostProcessPipeline;
using Bones::Framebuffers::PostProcess::PostProcessFramebuffer;
using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;
using Bones::Shaders::PostProcess::BasePostProcessShader;


Engine* engine;
Scene* scene;

Uint32 start;
const int FPS = 60;

NightVisionPostProcessFramebuffer* nightVisionPostProcessBuffer = nullptr;

#if EMSCRIPTEN_RUNTIME 
void Render()
{
	engine->Run();
}
#endif 


void AddDebugLightsToScene()
{
	BaseGeometry* geometry = GeometryManager::GetOrCreateBoxGeometry();

	int index = 0;
	for (PointLight* light : scene->GetPointLights())
	{
		StandardMaterial* material = MaterialManager::CreateStandardMaterial("debug_light_" + to_string(index++), STANDARD_MATERIAL_DISABLE_LIGHTS);
		vec3 color = light->m_color;
		material->SetDiffuseColor(vec4(color.x, color.y, color.z, 1.0));
		StandardMaterialMesh* mesh = MeshManager::CreateStandardMaterialMesh(geometry, material);
		SceneObject* obj = new SceneObject(scene, mesh);
		obj->GetTransform().SetScale(vec3(0.2f, 0.2f, 0.2f));
		obj->GetTransform().SetPosition(light->GetPosition());
		scene->AddSceneObject(obj);
	}
}

//SceneObject* box1, * box2, * box3, * box4, * box5;

void OnEngineInitialized(const IEvent& evt)
{

}

int main(int argc, char* argv[])
{
	engine = new Engine();
	engine->UseUserInterface();
	engine->m_onInitializedEvent += &OnEngineInitialized;


	Uint32 testTime = 0;
	engine->m_pollEvents = [&](SDL_Event evt) 
	{
		
	};
	engine->m_updateEvent = [](Uint32 dt)
	{

	};
	engine->m_drawEvent = []() {};
	engine->m_destroyEvent = []()
	{
	};

	engine->Load();
	engine->Initialize();
	std::cout << engine->GetRenderer()->GetInfoLog() << std::endl;

	scene = SceneManager::CreateScene("main_scene");

	scene->UseDefaultSkybox();


	StandardMaterialOptions opts;
	opts.useDiffuseMap = true;
	opts.useSpecularMap = true;

	unsigned long a = opts.ConvertToUL();
	unsigned long b = MATERIAL_SHADER_USE_DIFFUSE_MAP | MATERIAL_SHADER_USE_SPECULAR_MAP;

	StandardMaterial* boxMaterial = MaterialManager::CreateStandardMaterial("boxMaterial", opts);
	boxMaterial->SetDiffuseTexture("resources/textures/crate0_diffuse.png");
	StandardMaterial* texturelessBoxMaterial = MaterialManager::CreateStandardMaterial("box2Material", {});
	texturelessBoxMaterial->SetDiffuseColor(vec4(0.4, 0.4, 0.4, 1.0));
	StandardMaterial* floorMaterial = MaterialManager::CreateStandardMaterial("floorMaterial", opts);
	floorMaterial->SetDiffuseTexture("resources/textures/Stone_Floor.png");
	opts.useDiffuseMap = true;


	// add floor 
	QuadGeometry* quadGeometry = GeometryManager::GetOrCreateQuadGeometry();
	SceneObject* floor = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(quadGeometry, floorMaterial), "floor");
	floor->GetTransform().SetPosition(vec3(0, -1, 0));
	floor->GetTransform().SetScale(vec3(50, 1, 50));
	scene->AddSceneObject(floor);

	opts.useSpecularMap = true;
	StandardMaterial* boxWithSpecularMat = MaterialManager::CreateStandardMaterial("boxWithSpec", opts);
	boxWithSpecularMat->SetDiffuseTexture("resources/textures/container2.png");
	boxWithSpecularMat->SetSpecularTexture("resources/textures/container2_specular.png");
	boxWithSpecularMat->m_specularIntensity = 30;
	boxWithSpecularMat->m_specularShininess = 16;

	scene->AddPointLight(new PointLight(vec3(3.0f, 1.f, -3.f), vec3(1, 0, 0)));
	scene->AddPointLight(new PointLight(vec3(-4.0f, 3.f, -4.f), vec3(0, 0, 1)));
	//scene->AddPointLight(new PointLight(vec3(-3.0f, 1.f, 5.f), vec3(0, 1, 0)));
	//scene->AddPointLight(new PointLight(vec3(5.0f, 3.f, 6.f)));
	//scene->AddSpotLight(new SpotLight());

	//// add boxes 
	//boxMaterial->SetRenderWireframe(true);
	//BoxGeometry* boxGeometry = GeometryManager::GetOrCreateBoxGeometry();
	//auto box1 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(boxGeometry, boxMaterial));
	//box1->m_name = "box 1";
	//box1->UseDrawOutline(true);
	//auto box2 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(boxGeometry, boxMaterial));
	//box2->UseDrawOutline(true, glm::vec4(1, 0.3, 0.3, 0.8));
	//box2->m_name = "box 2";
	//auto box3 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(boxGeometry, texturelessBoxMaterial));
	//box3->UseDrawOutline(true); 
	//box3->m_name = "box 3";
	//auto box4 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(boxGeometry, boxWithSpecularMat));
	//box4->m_name = "box 4";
	//auto box5 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(boxGeometry, boxWithSpecularMat));
	//box5->m_name = "box 5";
	//scene->AddSceneObject(box1);
	//scene->AddSceneObject(box2);
	//scene->AddSceneObject(box3);
	//scene->AddSceneObject(box4);
	//scene->AddSceneObject(box5);
	//box1->GetTransform().SetPosition(vec3(4, 3, 2));
	//box2->GetTransform().SetPosition(vec3(-4, 0, 3));
	//box3->GetTransform().SetPosition(vec3(-3, 4, 3));
	//box4->GetTransform().SetPosition(vec3(-2, 1, 2));
	//box5->GetTransform().SetPosition(vec3(4, 2, 0));

	//// add grass 
	/*QuadGeometry* grassQuadGeometry = GeometryManager::GetOrCreateQuadGeometry();

	StandardMaterial* grassMaterial = MaterialManager::CreateStandardMaterial("grassMaterial", {});
	grassMaterial->m_specularIntensity = 0;
	grassMaterial->m_specularShininess = 0;
	grassMaterial->SetDiffuseTexture("resources/textures/grass.png");

	SceneObject* grass1 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, grassMaterial));
	grass1->m_transform->m_position = vec3(1, 0, 1);
	grass1->m_transform->m_scale = vec3(3, 3, 3);
	grass1->m_transform->m_rotation.x = radians(-90.0f);

	grass1->m_hasTransparency = true;
	SceneObject* grass2 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, grassMaterial));
	grass2->m_transform->m_position = vec3(1, 0, -5);
	grass2->m_transform->m_scale = vec3(3, 3, 3);
	grass2->m_transform->m_rotation.x = radians(-90.0f);
	grass2->m_hasTransparency = true;

	SceneObject* grass3 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, grassMaterial));
	grass3->m_transform->m_position = vec3(2, 0, 5);
	grass3->m_transform->m_scale = vec3(3, 3, 3);
	grass3->m_transform->m_rotation.x = radians(-90.0f);
	grass3->m_hasTransparency = true;

	SceneObject* grass4 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, grassMaterial));
	grass4->m_transform->m_position = vec3(5, 0, 2);
	grass4->m_transform->m_scale = vec3(3, 3, 3);
	grass4->m_transform->m_rotation.x = radians(-90.0f);
	grass4->m_hasTransparency = true;

	SceneObject* grass5 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, grassMaterial));
	grass5->m_transform->m_position = vec3(-3, 0, -4);
	grass5->m_transform->m_scale = vec3(3, 3, 3);
	grass5->m_transform->m_rotation.x = radians(-90.0f);
	grass5->m_hasTransparency = true;

	scene->AddSceneObject(grass1);
	scene->AddSceneObject(grass2);
	scene->AddSceneObject(grass3);
	scene->AddSceneObject(grass4);
	scene->AddSceneObject(grass5);*/

	//// add windows
	//StandardMaterial* windowMaterial = MaterialManager::CreateStandardMaterial("windowMaterial", {});
	//windowMaterial->m_specularIntensity = 0;
	//windowMaterial->m_specularShininess = 0;
	//windowMaterial->SetDiffuseTexture("resources/textures/window.png");

	//SceneObject* window1 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, windowMaterial));
	//window1->m_transform->m_position = vec3(1, 1, -2);
	//window1->m_transform->m_scale = vec3(3, 3, 3);
	//window1->m_transform->m_rotation.x = radians(-90.0f);
	//window1->m_hasTransparency = true;


	//SceneObject* window2 = new SceneObject(scene, MeshManager::CreateStandardMaterialMesh(grassQuadGeometry, windowMaterial));
	//window2->m_transform->m_position = vec3(6, 2, -5);
	//window2->m_transform->m_scale = vec3(3, 3, 3);
	//window2->m_transform->m_rotation.x = radians(-90.0f);
	//window2->m_hasTransparency = true;

	//scene->AddSceneObject(window1);
	//scene->AddSceneObject(window2);

	SceneObjectLoader scnObjLoader;
	/*auto sceneObjs = scnObjLoader.LoadFromGltfFile(*scene, "resources/models/non-working.gltf");
	sceneObjs[0]->GetTransform().SetScale(0.2f, 0.2f, 0.2f);*/
	//auto sceneObjs2 = scnObjLoader.LoadFromGltfFile(*scene, "resources/models/working.gltf");
	//sceneObjs2[0]->GetTransform().SetScale(0.2f, 0.2f, 0.2f);
	//auto rayman = scnObjLoader.LoadFromObjFile(*scene, "resources/models/rayman/rayman_3.obj");
	//rayman[0]->GetTransform().SetScale(0.1, 0.1, 0.1);


	AddDebugLightsToScene();

	//scene->m_postProcessPipeline->AddSharpenEffect();
	//scene->m_postProcessPipeline->AddGrayScaleOrderedDitheringEffect();
	// scene->m_postProcessPipeline->AddDetectEdgeEffect();
	 scene->m_postProcessPipeline->AddNightVisionEffect()->LightNoisePreset();


#if EMSCRIPTEN_RUNTIME 
	// 1 stands for EM_TIMING_RAF  1: 60fps, 2: 30fps
	emscripten_set_main_loop(Render, 0, 1);
	emscripten_set_main_loop_timing(1, 1);
#else 
	engine->Run();
	delete engine;
#endif 

	return 1;
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

const Engine& GetEngine()
{
	return *engine;
}


void LightNoisePresetEffect()
{
	if (nightVisionPostProcessBuffer == nullptr)
	{
		nightVisionPostProcessBuffer = scene->m_postProcessPipeline->AddNightVisionEffect();
	}

	nightVisionPostProcessBuffer->LightNoisePreset();
}

void NoisePresetEffect()
{
	if (nightVisionPostProcessBuffer == nullptr)
	{
		nightVisionPostProcessBuffer = scene->m_postProcessPipeline->AddNightVisionEffect();
	}
	nightVisionPostProcessBuffer->NoisyPreset();
}

void NoVignetteNoisePresetEffect()
{
	if (nightVisionPostProcessBuffer == nullptr)
	{
		nightVisionPostProcessBuffer = scene->m_postProcessPipeline->AddNightVisionEffect();
	}
	nightVisionPostProcessBuffer->NoiseNoVignettePreset();
}

void LightNoiseNoVignettePresetEffect()
{
	if (nightVisionPostProcessBuffer == nullptr)
	{
		nightVisionPostProcessBuffer = scene->m_postProcessPipeline->AddNightVisionEffect();
	}
	nightVisionPostProcessBuffer->LightNoVignettePreset();
}

EMSCRIPTEN_BINDINGS(Main)
{
	emscripten::function("GetEngine", &GetEngine, allow_raw_pointers());
	emscripten::function("GetEngine", &GetEngine);

	emscripten::function("LightNoisePresetEffect", &LightNoisePresetEffect);
	emscripten::function("NoisePresetEffect", &NoisePresetEffect);
	emscripten::function("NoVignetteNoisePresetEffect", &NoVignetteNoisePresetEffect);
	emscripten::function("LightNoiseNoVignettePresetEffect", &LightNoiseNoVignettePresetEffect);
}

#endif 
