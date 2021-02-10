#pragma once

#include "ShadowMap.hpp"

namespace Bones
{
	namespace Shadow
	{

		/// <summary>
		/// ShadowMap OpenGL_4
		/// </summary>
		class ShadowMapOpenGL4 final : public ShadowMap
		{
		public:
			void Initialize() override;
		};
	}
}