#pragma once

#ifndef QUAD_SCREEN_GEOMETRY_H

#define QUAD_SCREEN_GEOMETRY_H

#include "QuadScreenInterleavedBuffer.hpp"
#include "BaseGeometry.hpp"
#include "BuffersManager.hpp"

using Bones::Geometry::BaseGeometry;
using Bones::Buffers::QuadScreenBuffers::QuadScreenInterleavedBuffer;
using Bones::Managers::BuffersManager;

namespace Bones
{
	namespace Geometry
	{
		class QuadScreenGeometry final : public BaseGeometry
		{
		public:
			QuadScreenGeometry() : BaseGeometry(BuffersManager::GetOrCreateInterleavedBuffer<QuadScreenInterleavedBuffer>(), 12) {}
		};
	}
}

#endif // !QUAD_SCREEN_GEOMETRY_H
