#pragma once

#include "BaseGeometry.hpp"
#include "CubeInterleavedBuffer.hpp"
#include "BuffersManager.hpp"

using  Bones::Buffers::CubeInterleavedBuffer;
using Bones::Managers::BuffersManager;

namespace Bones
{
	namespace Geometry
	{
		/// <summary>
		/// The Box Geometry.
		/// </summary>
		class BoxGeometry final : public BaseGeometry
		{
		public:
			BoxGeometry() : BaseGeometry(BuffersManager::GetOrCreateInterleavedBuffer<CubeInterleavedBuffer>(), 36)
			{}	
		};
	}
}