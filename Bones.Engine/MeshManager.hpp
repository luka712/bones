#pragma once

#ifndef MESH_MANAGER_H

#define MESH_MANAGER_H

#include "core_types.h"
#include "core_types.h"
#include <vector>

using std::vector;
using std::find;

namespace Bones
{
	namespace Mesh
	{
		class StandardMaterialMesh;
	}
	namespace Geometry
	{
		class BaseGeometry;
	}
	namespace Materials
	{
		class StandardMaterial;
	}
}

using Bones::State;
using Bones::Mesh::StandardMaterialMesh;
using Bones::Geometry::BaseGeometry;
using Bones::Materials::StandardMaterial;

namespace Bones
{
	namespace Managers
	{
		class MeshManager
		{
		private:
			static vector< StandardMaterialMesh*> m_meshes;
		public:
			static State m_state;
			static StandardMaterialMesh* CreateStandardMaterialMesh(BaseGeometry* geometry, StandardMaterial* material);
			static void Destroy(StandardMaterialMesh* mesh);

			static void Destroy();
		};
	}
}

#endif // !MESH_MANAGER_H

