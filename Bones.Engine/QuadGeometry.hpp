#pragma once

#include "BaseGeometry.hpp"
#include "QuadInterleavedBuffer.hpp"
#include "QuadIndexBuffer.hpp"
#include "BuffersManager.hpp"

using namespace Bones::Buffers;
using Bones::Managers::BuffersManager;

namespace Bones
{
	namespace Geometry
	{
		/// <summary>
		/// The quad geometry.
		/// </summary>
		class QuadGeometry final : public BaseGeometry
		{
		public:
			QuadGeometry() : BaseGeometry(BuffersManager::GetOrCreateInterleavedBuffer<QuadInterleavedBuffer>(), BuffersManager::GetOrCreateIndexBuffer<QuadIndexBuffer>())
			{}
		};
	}
}
