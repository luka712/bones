#pragma once

#ifndef UI_TOOLS_EVENT_MANAGER_H

#define UI_TOOLS_EVENT_MANAGER_H

#include "Constants.hpp"
#include <functional>
#include <vector>

using Bones::State;
using std::vector;

class SceneObject;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			class BaseToolUIComponent;

			class UIToolsEventManager final
			{
			private:
				static std::vector < std::function<void(Bones::Event<SceneObject&>)>> m_sceneViewSceneObjectSelectedEvents;
				static std::vector <std::function<void(Bones::Event<SceneObject&>)>> m_sceneObjectNameChangedEvents;
			public:
				static Bones::State m_state;

				static void Initialize();
				static void Destroy();

				// -- events
				static void OnSceneViewSceneObjectSelected(std::function<void(Bones::Event<SceneObject&>)> cb);
				static void RaiseOnSceneViewSceneObjectSelected(const Bones::Event<SceneObject&>& evt);
				
				static void OnSceneObjectNameChanged(std::function<void(Bones::Event<SceneObject&>)> cb);
				static void RaiseOnSceneObjectNameChanged(const Bones::Event<SceneObject&>& evt);
				static void RemoveOnSceneObjectNameChanged(std::function<void(Bones::Event<SceneObject&>)> cb);
			};
		}
	}
}

#endif // !UI_TOOLS_EVENT_MANAGER_H
