#pragma once
#ifndef SCENE_OBJECT_UI_SCENE_VIEW_COMPONENT_H

#define SCENE_OBJECT_UI_SCENE_VIEW_COMPONENT_H

#include "BaseSceneViewEntryComponent.hpp"
#include "Constants.hpp"
#include "SelectableLabelUIComponent.hpp"
#include <functional>

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class SelectableLabelUIComponent;
		}
	}
}

using std::function;
using namespace Bones::UI::Core;
class SceneObject;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			class SceneViewUIToolComponent;

			namespace SceneView
			{
				/// <summary>
				/// Scene object label as seen in scene view.
				/// </summary>
				class SceneObjectSceneViewComponent final : public BaseSceneViewEntryComponent
				{
				private:
					SelectableLabelUIComponent* m_label;
					SceneObject* m_sceneObject;

					// View component is parent view component, since this belongs to certaing view -> tree
					SceneViewUIToolComponent* m_viewParentPtr;

					// -- event listener
					std::function<void(Bones::Event<SceneObject&> evt)> m_onSceneObjectNameChanged;
				public:
#pragma region EVENTS
					std::function<void(Bones::Event<SceneObjectSceneViewComponent&> evt)> m_onSelected = [](Bones::Event<SceneObjectSceneViewComponent&>) -> void {};
#pragma endregion

					// -- members 
					Bones::State m_state = Bones::State::New;

					SceneObjectSceneViewComponent(SceneObject* obj, SceneViewUIToolComponent* sceneViewParent);

					// -- interface
					void Initialize();
					void SetSelected(bool val);
					bool IsSelected();

					~SceneObjectSceneViewComponent();
				};
			}
		}
	}
}

#endif // !SCENE_OBJECT_UI_SCENE_VIEW_COMPONENT_H
