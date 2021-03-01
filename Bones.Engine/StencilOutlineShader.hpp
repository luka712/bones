#pragma once

#ifndef STENCILOUTLINESHADER_H

#define STENCILOUTLINESHADER_H

#include "vendor.h"
#include "BaseShader.hpp"

using Bones::Shaders::BaseShader;

namespace Bones
{
	namespace Shaders
	{
		namespace Stencil
		{
			/// <summary>
			/// Stencil outline shader.
			/// </summary>
			class StencilOutlineShader : public BaseShader
			{
			public:
				struct
				{
					GLint projectionLocation;
					GLint viewLocation;
					GLint transformLocation;
					GLint colorLocation;
				} m_locations;

				StencilOutlineShader();

				void Initialize() override;
				void Load() override;
			};
		}
	}
}

#endif // !STENCILOUTLINESHADER_H
