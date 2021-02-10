#pragma once

#ifndef SCENE_MANAGER_H

#define SCENE_MANAGER_H

#include <string>
#include <map>
#include <functional>
#include <vector>

namespace Bones
{
	class Scene;
}

using std::function;
using std::vector;
using std::map;
using std::string;
using Bones::Scene;

namespace Bones
{
	namespace Managers
	{
		class SceneManager
		{
		private:
			static map<string, Scene*> m_scenes;
			static vector<function<void(Scene& scene)>> m_onSceneCretedEvents;
		public:
			static Scene* m_currentScene;
			static Scene* Get(const string& name);
			static Scene* CreateScene(const string& name);
			
			static void OnSceneCreated(function<void(Scene& scene)> cb);

			static void Delete(const string& name);
			static void Destroy();
		};
	}
}

#endif // !SCENE_MANAGER_H
