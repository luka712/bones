#pragma once

#ifndef SCENE_OBJECT_UI_TOOL_COMPONENT_H

#define SCENE_OBJECT_UI_TOOL_COMPONENT_H

#include "Constants.hpp"
#include "BaseToolUIComponent.hpp"

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class WindowUIComponent;
			class TextUIComponent;
			class CheckboxUIComponent;
		}
	}
}

using namespace Bones::UI::Core;

class SceneObject;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			/// <summary>
			/// Inspector component that represents scene object.
			/// </summary>
			class SceneObjectInspectorComponent final : public BaseToolUIComponent
			{
			private:
				SceneObject* m_sceneObjectRef;
				WindowUIComponent* m_parentWindow;
				TextUIComponent* m_nameText;
				CheckboxUIComponent* m_activeCheckbox;
			public:
				Bones::State m_state = Bones::State::New;
				bool m_active = false;
				SceneObjectInspectorComponent(WindowUIComponent* parentWindow, SceneObject* sceneObject);
				~SceneObjectInspectorComponent();
				void Initialize();
				void Destroy();
			};
		}
	}
}

#endif // !SCENE_OBJECT_UI_TOOL_COMPONENT_H
