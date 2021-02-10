#pragma once 

#include <string>
#include "Constants.hpp"
#include "Scene.hpp"
#include <functional>


using namespace std;
using namespace Bones::Materials;
//using namespace Bones::Shadow;

namespace Bones
{
	namespace Geometry
	{
		class BaseGeometry;
	}
}

using Bones::Geometry::BaseGeometry;

namespace Bones
{
	namespace Renderer
	{
		typedef void(*RendererInitializedCallback)(SDL_Window*);

		struct RendererInitializeState
		{
			bool initialized;
			string error;
		};

		class BaseRenderer
		{
		protected:
			vector<SceneObject*> m_opaqueRenderPassObjects;
			vector<SceneObject*> m_transparentRenderPassObjects;
			vector<SceneObject*> m_collectStencilPassObjects;

			// use this to optimize rendering.
			BaseShader* m_currentShader;
			BaseGeometry* m_currentGeometry;

			const string m_viewMatrixRef = "u_view";
			const string m_projectionMatrixRef = "u_projection";

			virtual int MajorVersion() const = 0;
			virtual int MinorVersion() const = 0;

			// - Creation 
			virtual void CreateWindowAndRenderer();

			/// <summary>
			/// Prepass to generate shadow maps.
			/// </summary>
			/// <returns></returns>
			void DirectionalShadowMapPass(Scene& scene);

			/// <summary>
			/// Prepass to generate shadow maps.
			/// </summary>
			virtual void OmniDirectionalShadowMapPass(Scene& scene);

			/// <summary>
			/// Render of scene. To be use by shadows and main pass.
			/// </summary>
			void RenderScene(Scene& scene);

			/// <summary>
			/// The main pass of scene, which is run after shadow maps.
			/// </summary>
			void RenderPass(Scene& scene, const vector<SceneObject*> passObjects);

			/// <summary>
			/// The stencil pass. 
			/// Uses m_sceneObjectStencilPass objects;
			/// </summary>
			void StencilPass();

			void StandardMaterialRendering();

		public:
			vec4 m_clearColor = vec4(0.4, 0.7, 0.8, 1);
			SDL_Window* m_window = nullptr;
			SDL_Renderer* m_renderer = nullptr;
			SDL_GLContext m_glContext = nullptr;
			virtual ~BaseRenderer();

			const vec4& GetClearColor() const noexcept { return m_clearColor; }
			void SetClearColor(vec4 color) noexcept;
			void SetClearColor(float r, float g, float b, float a = 1.0f) noexcept;


			virtual RendererInitializeState Initialize();

			/// <summary>
			/// Main rendering function
			/// </summary>
			virtual void Render(Scene& scene);

			/// <summary>
			/// Swap window call should be called after render function. Swaps the prepeared buffer.
			/// </summary>
			void SwapWindow();
			
			virtual void Destroy();
			virtual const string GetInfoLog() const;
		};
	}
}

