#pragma once

#ifndef GEOMETRY_MANAGER_H

#define GEOMETRY_MANAGER_H

namespace Bones 
{
	namespace Geometry
	{
		class QuadScreenGeometry;
		class EnvironmentMapGeometry;
		class BoxGeometry;
		class QuadGeometry;
	}
}

using Bones::Geometry::QuadScreenGeometry;
using Bones::Geometry::EnvironmentMapGeometry;
using Bones::Geometry::BoxGeometry;
using Bones::Geometry::QuadGeometry;

namespace Bones
{
	namespace Managers
	{
		class GeometryManager
		{
		private:
			static QuadScreenGeometry* m_quadScreenGeometry;
			static EnvironmentMapGeometry* m_environmentMapGeometry;
			static BoxGeometry* m_boxGeometry;
			static QuadGeometry* m_quadGeometry;

		public:
			static QuadScreenGeometry* GetOrCreateQuadScreenGeometry();
			static EnvironmentMapGeometry* GetOrCreateEnvironmentMapGeometry();
			static BoxGeometry* GetOrCreateBoxGeometry();
			static QuadGeometry* GetOrCreateQuadGeometry();

			static void Delete();
		};
	}
}

#endif // !GEOMETRY_MANAGER_H
