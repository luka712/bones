#pragma once

#include <string>

namespace Bones
{
	class Scene;
}

class SceneObject;
using Bones::Scene;

namespace Bones
{
	namespace Loaders 
	{
		/// <summary>
		/// The scene object loader.
		/// </summary>
		class SceneObjectLoader final
		{
		public:
			vector<SceneObject*> LoadFromObjFile(Scene& scene, const string& path);
			vector<SceneObject*> LoadFromGltfFile(Scene& scene, const string& path);
		};
	}
}
