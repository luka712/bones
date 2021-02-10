#pragma once

#ifndef MATERIAL_MANAGER_H

#define MATERIAL_MANAGER_H

#include <map>
#include <string>
#include "MaterialStructs.hpp"

namespace Bones
{
	namespace Materials
	{
		class StandardMaterial;
	}
}

using std::map;
using std::string;
using Bones::Materials::StandardMaterial;
using Bones::Materials::StandardMaterialOptions;

namespace Bones
{
	namespace Managers
	{
		class MaterialManager
		{
		private:
			// phong
			static map<string, StandardMaterial*> m_standardMaterialsCache;
		public:
			// StandardMaterial& operator[](string name);

			/// <summary>
			/// Creates the material shader. If one exists overwrites.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="opts">The material shader options.</param>
			/// <returns></returns>
			static StandardMaterial* CreateStandardMaterial(const string& name, StandardMaterialOptions opts);

			/// <summary>
			/// Creates the material shader. If one exists it is overriden.
			/// </summary>
			static StandardMaterial* CreateStandardMaterial(const string& name, standard_material_options opts);

			/// <summary>
			/// Deletes the material shader.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <returns>True if removed, otherwise false.</returns>
			static bool DeleteStandardMaterial(const string& name);

			static void Delete();
		};
	}
}

#endif // !MATERIAL_MANAGER_H
