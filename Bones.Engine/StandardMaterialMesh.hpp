#pragma once

#ifndef STANDARD_MATERIAL_MESH_H

#define STANDARD_MATERIAL_MESH_H

#include "BaseMesh.hpp"

namespace Bones
{
	namespace Geometry
	{
		class BaseGeometry;
	}

	namespace Materials
	{
		class StandardMaterial;
	}
}

using Bones::Mesh::BaseMesh;
using Bones::Geometry::BaseGeometry;
using Bones::Materials::StandardMaterial;

namespace Bones
{
	namespace Mesh
	{
		class StandardMaterialMesh : public BaseMesh
		{
		public:
			StandardMaterial* m_material;
			StandardMaterialMesh(BaseGeometry* geometry, StandardMaterial* material);
			~StandardMaterialMesh();

			void UseMesh() override;

			/// <summary>
			/// The render function.
			/// </summary>
			void Render() override;
		};
	}
}

#endif // !STANDARD_MATERIAL_MESH_H