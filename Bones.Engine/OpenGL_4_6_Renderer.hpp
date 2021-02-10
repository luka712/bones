#pragma once 

#include "BaseRenderer.hpp"

using namespace Bones::Renderer;

namespace Bones
{
	namespace Renderer
	{
		class OpenGL_4_6_Renderer final : public BaseRenderer
		{
		private:
			void PointLightPass( Scene& scene, PointLight& light);
			void SpotLightPass( Scene& scene, SpotLight& light);
		protected:
			inline int MajorVersion() const
			{
				return 4;
			}

			inline int MinorVersion() const
			{
				return 6;
			}

			void OmniDirectionalShadowMapPass(Scene& scene) override;
		};
	}

}



