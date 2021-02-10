#pragma once

#include "BaseGeometry.hpp"
#include "SkyboxVertexBuffer.hpp"
#include "BuffersManager.hpp"

#ifndef ENVIRONMENT_MAP_GEOMETRY_H

#define ENVIRONMENT_MAP_GEOMETRY_H

using Bones::Managers::BuffersManager;

namespace Bones
{
	namespace Geometry
	{
		/// <summary>
		/// The Box Geometry.
		/// </summary>
		class EnvironmentMapGeometry final : public BaseGeometry
		{
		public:
			EnvironmentMapGeometry() : BaseGeometry(BuffersManager::GetOrCreateVertexBuffer<SkyboxVertexBuffer>(), 36)
			{}
		};
	}
}

#endif // !ENVIRONMENT_MAP_GEOMETRY_H