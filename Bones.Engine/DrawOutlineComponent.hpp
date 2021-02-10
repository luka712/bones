#pragma once

#include "BaseDrawComponent.hpp"
#include "StencilOutlineShader.hpp"
#include "BaseCamera.hpp"

using Bones::Components::Draw::BaseDrawComponent;
using Bones::Shaders::Stencil::StencilOutlineShader;
using Bones::Camera::BaseCamera;

namespace Bones
{
	namespace Components
	{
		namespace Draw
		{
			/// <summary>
			/// Component that uses stencil buffer to draw outline of object.
			/// </summary>
			class DrawOutlineComponent : public BaseDrawComponent
			{
			public:
				StencilOutlineShader* m_shader;
				glm::vec4 m_color = glm::vec4(0,0,0,0);
				float m_scaleFactor = 1.05f;

				DrawOutlineComponent(SceneObject* sceneObj);
				~DrawOutlineComponent();

				void Initialize() override;
				void Draw() override;
			};
		}
	}
}
