#pragma once
#ifndef SCENE_VIEW_ENTRY_COMPONENT_H

#define SCENE_VIEW_ENTRY_COMPONENT_H

#include "BaseToolUIComponent.hpp"
#include "Constants.hpp"

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
				class BaseSceneViewEntryComponent : public BaseToolUIComponent
				{
				protected:
					// View component is parent view component, since this belongs to certaing view -> tree
					SceneViewUIToolComponent* m_viewParentPtr;
				public:
					Bones::State m_state = Bones::State::New;
					
					// -- interface
					virtual void SetSelected(bool val) = 0;
					virtual bool IsSelected() = 0;
				};
			}
		}
	}
}

#endif // !SCENE_VIEW_ENTRY_COMPONENT_H
