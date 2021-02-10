#pragma once

#ifndef BASE_MESH_H

#define BASE_MESH_H

#include "Constants.hpp"

namespace Bones
{
	namespace Materials
	{
		class BaseMaterial;
	}

	namespace Geometry
	{
		class BaseGeometry;
	}
}

using Bones::Materials::BaseMaterial;
using Bones::Geometry::BaseGeometry;

class SceneObject;

namespace Bones
{
	namespace Mesh
	{
		/// <summary>
		/// Mesh is data structure that holds geometry and material.
		/// Geometry is collection of attributes, material is abstracted shader definitions with textures.
		/// </summary>
		class BaseMesh
		{	
		public:
			State m_state = State::New;

			// Scene object that this mesh belongs to.
			SceneObject* m_sceneObjectParent;
			
			// Geometry and material that belong tho this mesh.
			BaseMaterial* m_material;
			BaseGeometry* m_geometry;
			BaseMesh(BaseGeometry* geometry, BaseMaterial* material);

			void AttachToParent(SceneObject& sceneObject);

			void Initialize();

			/// <summary>
			/// Use mesh. Sends all the uniforms to gpu and binds textures.
			/// </summary>
			virtual void UseMesh();

			/// <summary>
			/// Bind textures.
			/// </summary>
			virtual void Render();

			virtual ~BaseMesh();
		};

	}
}

#endif // !BASE_MESH_H