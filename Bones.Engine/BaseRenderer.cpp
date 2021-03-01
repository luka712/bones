#include "BaseRenderer.hpp"
#include "StandardMaterial.hpp"
#include "StandardMaterialMesh.hpp"
#include "BasePostProcessPipeline.hpp"
#include "OpenGL_ES_3_0_Renderer.hpp"
#include "MaterialShader.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "MaterialShaderStructs.hpp"
#include "Skybox.hpp"
#include "BaseGeometry.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"


using Bones::Shaders::Material::MaterialShader;
using Bones::Materials::StandardMaterial;
using Bones::PostProcessPipeline::BasePostProcessPipeline;
using namespace Bones::Shaders::Material;

/*
	Rendering :
	-	Render
		-	DirectionalShadowPass
			-	ShadowStuff
			-	RenderScene
		-	OmniDirectionalShadowPass -> includes RenderScene
			-	ShadowStuff
			-	RenderScene
		-	RenderPass ->
			-	Use Shadow Stuff
			-	RenderScene

*/

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	//fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	//	(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	//	type, severity, message);
}

using namespace std;
using namespace Bones::Renderer;
using namespace Bones::Materials;

void BaseRenderer::CreateWindowAndRenderer()
{
	if (SDL_CreateWindowAndRenderer(DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL, &m_window, &m_renderer) < 0)
	{
		throw new runtime_error(SDL_GetError());
	}
}

void BaseRenderer::SetClearColor(vec4 color) noexcept
{
	m_clearColor = color;
}

void BaseRenderer::SetClearColor(float r, float g, float b, float a) noexcept
{
	m_clearColor.x = r;
	m_clearColor.y = g;
	m_clearColor.z = b;
	m_clearColor.w = a;
}

RendererInitializeState BaseRenderer::Initialize()
{
	m_currentShader = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return { false, SDL_GetError() };
	}

	// version needs to be setup before renderer creation, must use ES for webgl context.
#if TARGET_OPENGL_4_6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MajorVersion());
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MinorVersion());
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

	CreateWindowAndRenderer();
	
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr)
	{
		return { false, SDL_GetError() };
	}


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_CULL_FACE);

	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// SDL_ShowCursor(SDL_DISABLE);

		// Setup viewport size
	glViewport(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);

	SwapWindow();

#if !EMSCRIPTEN_RUNTIME
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		auto error = (const char*)(glewGetErrorString(glewError));
		return { false, string(error) };
	}
	glDebugMessageCallback(MessageCallback, 0);
	glEnable(GL_DEBUG_OUTPUT);
#endif

	return { true };
}


void BaseRenderer::DirectionalShadowMapPass(Scene& scene)
{
	//// get vars 
	//DirectionalLight& light = *scene.GetDirectionalLight();
	//DirectionalLightShadowMap& shadowMap = *light.GetShadowMap();
	//DirectionalShadowShader& shader = shadowMap.GetShader();

	//// start program
	//shader.UseProgram();

	//// set viewport
	//glViewport(0, 0, shadowMap.GetShadowWidth(), shadowMap.GetShadowHeight());

	//// use framebuffer to write to and clear it
	//shadowMap.BindFramebuffer();
	//glClear(GL_DEPTH_BUFFER_BIT);

	//shader.UseLightProjectionViewLocation(light.GetLightProjectionViewMatrix());

	//shader.Validate();
	//
	//RenderScene(scene);

	//// TO DEFAULT BUFFER 
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void BaseRenderer::RenderPass(Scene& scene, const vector<SceneObject*> passObjects)
{
	m_currentShader = nullptr;
	for (SceneObject* sceneObject : passObjects)
	{
		if (sceneObject->m_drawOutline != nullptr)
		{
			m_collectStencilPassObjects.push_back(sceneObject);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}
		else
		{
			glStencilMask(0x00);
		}

		const vector<BaseMesh*>& meshes = sceneObject->GetMeshes();
		for (StandardMaterialMesh* mesh : (const vector<StandardMaterialMesh*>&)meshes)
		{
			StandardMaterial* material = mesh->m_material;
			MaterialShader& shader = *material->m_shader;

			// shader.Validate();

			// optimize. Only if shader has changed re-reneder lights and camera.
			if (m_currentShader != &shader)
			{
				m_currentShader = &shader;		
				shader.UseProgram();
			}

			BaseCamera& camera = scene.GetActiveCamera();
			const vec3& cameraPos = camera.GetTransformComponent().GetPosition();

			// camera
			camera.UseCamera(shader);

			// ambient light
			if (scene.m_ambientLight != nullptr)
			{
				scene.m_ambientLight->UseLight(shader);
			}

			// directional lights
			for (size_t i = 0; i < scene.m_directionalLights.size(); i++)
			{
				DirectionalLightLocations location = shader.m_directionalLightLocations[i];
				scene.m_directionalLights[i]->UseLight(location);
			}
			shader.SetInt(shader.m_directionalLightCountLocation, scene.m_directionalLights.size());
			// read into texture 1 and set shadow map location to use texture unit 1
		/*	scene.GetDirectionalLight()->ReadShadowMap(GLTextureUnit::TEXTURE2, 0);
			glUniform1i(directionalLightLocations.shadowMapTextureLocation, 2);*/

			// point lights
			for (size_t i = 0; i < scene.m_pointLights.size(); i++)
			{
				PointLightLocations location = shader.m_pointLightsLocations[i];
				scene.m_pointLights[i]->UseLight(location);
				// pointLights[i]->ReadShadowMap(GLTextureUnit::TEXTURE3, i+1);

				// TODO: rethink texture binding.
				// glUniform1i(pointLightsLocations[i].shadowMapLocation, i);
			}
			shader.SetInt(shader.m_pointLightsCountLocation, static_cast<int>(scene.m_pointLights.size()));

			for (size_t i = 0; i < scene.m_spotLights.size(); i++)
			{
				SpotLightLocations location = shader.m_spotLightsLocations[i];
				scene.m_spotLights[i]->UseLight(location);

				// TODO: rethink texture binding.
				// glUniform1i(pointLightsLocations[i].shadowMapLocation, i);
				// spotLights[i]->ReadShadowMap(GLTextureUnit::TEXTURE3, i + 1);
			}
			shader.SetInt(shader.m_spotLightsCountLocation, static_cast<int>(scene.m_spotLights.size()));
		
			//}
			//glUniform1i(spotLightsLocations.spotLightsCountLocation, static_cast<int>(spotLights.size()));
		//}

			// transforms such as material spectifics and transform. Specific to material. bind textures such as diffuse, normal ( not shadow maps )
			mesh->UseMesh();
			// bind buffers, gl draw, unbind buffers
			mesh->Render();
		}
	}
}

// 
void BaseRenderer::RenderScene(Scene& scene)
{
	for (SceneObject* const& sceneObj : scene.GetObjects())
	{
		for (BaseMesh* const& mesh : sceneObj->GetMeshes())
		{
			mesh->UseMesh();
			// bind buffers, gl draw, unbind buffers
			mesh->Render();
		}
	}
}

void BaseRenderer::StencilPass()
{
	for (SceneObject* obj : m_collectStencilPassObjects)
	{
		if (m_currentShader != obj->m_drawOutline->m_shader)
		{
			m_currentShader = obj->m_drawOutline->m_shader;
			m_currentShader->UseProgram();
			// prepare for stencil pass
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00); // disable writing to the stencil buffer
			glDisable(GL_DEPTH_TEST); // disable to see outline through other objects 
		}

		const vector<BaseMesh*>& meshes = obj->GetMeshes();
		for (StandardMaterialMesh* mesh : (const vector<StandardMaterialMesh*>&)meshes)
		{
			// bind buffers, gl draw, unbind buffers
			obj->m_drawOutline->Draw();

			mesh->Render();
		}
	}

	// reset to defauls
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void BaseRenderer::Render(Scene& scene)
{
	ImGui::Render();

	// start of frame. Prepare arrays
	m_opaqueRenderPassObjects.clear();
	m_transparentRenderPassObjects.clear();

	const BaseCamera& camera = scene.GetActiveCamera();
	// transparent objects go to end. First reneder opaque objects, afterwared transparent ones.
	vector<SceneObject*> transparentObjects;
	for(SceneObject* scnObj: scene.m_sceneObjects)
	{
		// collect only if active.
		if (scnObj->m_active)
		{
			if (scnObj->m_hasTransparency)
			{
				m_transparentRenderPassObjects.push_back(scnObj);
			}
			else
			{
				m_opaqueRenderPassObjects.push_back(scnObj);
			}
		}
	}

	// Sort transparent objects
	sort(transparentObjects.begin(), transparentObjects.end(),
		[&camera]( SceneObject* a,  SceneObject* b) -> bool
	{ 
		return a->m_transform->DistanceFrom(*camera.m_transform) > b->m_transform->DistanceFrom(*camera.m_transform);
	});
	for (SceneObject* scnObj : transparentObjects)
	{
		m_transparentRenderPassObjects.push_back(scnObj);
	}

	m_collectStencilPassObjects.clear();
	m_collectStencilPassObjects.reserve(m_collectStencilPassObjects.size());

	//DirectionalShadowMapPass(scene);
	//OmniDirectionalShadowMapPass(scene);

	// on each frame enable depth test.
	scene.m_postProcessPipeline->Bind();
	glEnable(GL_DEPTH_TEST);

	// do nothing on fail or zfail, replace value on zpass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glViewport(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	
	RenderPass(scene, m_opaqueRenderPassObjects);

	// skybox
	if (scene.m_skybox != nullptr && scene.m_skybox->m_active)
	{
		scene.m_skybox->Draw(scene.GetActiveCamera());
	}
	RenderPass(scene, m_transparentRenderPassObjects);

	StencilPass();

	scene.m_postProcessPipeline->Draw();

	// disabled cached shader check 
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void BaseRenderer::SwapWindow()
{
	SDL_GL_SwapWindow(m_window);
}


const string BaseRenderer::GetInfoLog() const
{
	auto version = string((const char*)(glGetString(GL_VERSION)));
	auto vendor = string((const char*)glGetString(GL_VENDOR));
	auto rendererLog = string((const char*)glGetString(GL_RENDERER));
	auto shadersVersion = string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	return string("GL version:" + version + "\n"
		+ "Vendor: " + vendor + "\n"
		+ "GPU:" + rendererLog + "\n"
		+ "Shader language version:" + shadersVersion);
}

void BaseRenderer::Destroy()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Bones::Renderer::BaseRenderer::OmniDirectionalShadowMapPass(Scene& scene)
{
}


BaseRenderer::~BaseRenderer()
{
	Destroy();

	if (m_currentShader)
	{
		m_currentShader = nullptr;
	}
	if (m_currentGeometry)
	{
		m_currentGeometry = nullptr;
	}
}



#if EMSCRIPTEN_RUNTIME

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Renderer_JS)
{
	class_<BaseRenderer>("BaseRenderer")
		//.function("GetClearColor", [](BaseRenderer& self) -> vec4 { return self.GetClearColor(); })
		.function("SetClearColor", select_overload<void(float, float, float, float)>(&BaseRenderer::SetClearColor));

	class_<OpenGL_ES_3_0_Renderer, base<BaseRenderer>>("WebGL2Renderer")
		.constructor();
	//.function("GetClearColor", &Renderer::GetClearColor, allow_raw_pointers())
	//.function("SetClearColor", &Renderer::SetClearColor, allow_raw_pointers());
}

#endif 