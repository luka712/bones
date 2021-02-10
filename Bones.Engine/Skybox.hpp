#pragma once

#ifndef SKYBOX_H

#define SKYBOX_H

#include <string>
#include "Constants.hpp"

using std::string;

namespace Bones
{
	namespace Textures
	{
		class CubeTexture;
	}

	namespace Geometry
	{
		class EnvironmentMapGeometry;
	}

	namespace Shaders
	{
		namespace Environment
		{
			class SkyboxShader;
		}
	}

	namespace Camera
	{
		class BaseCamera;
	}
}

using Bones::Camera::BaseCamera;
using Bones::Textures::CubeTexture;
using Bones::Geometry::EnvironmentMapGeometry;
using Bones::Shaders::Environment::SkyboxShader;

namespace Bones
{
	namespace Environment
	{
		class Skybox
		{
		private:
			CubeTexture* m_texture;
			EnvironmentMapGeometry* m_geometry;
			SkyboxShader* m_shader;

			string str[6];

		public:
			State m_state = State::New;
			bool m_active = true;
			Skybox(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back);
			~Skybox();

			void Load();
			void Initialize();

			void Draw(const BaseCamera& camera);
		};
	}
}

#endif // !SKYBOX_H

