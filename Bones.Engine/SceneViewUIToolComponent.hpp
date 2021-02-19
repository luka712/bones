#pragma once

#ifndef SCENE_MENU_H

#define SCENE_MENU_H

#include <functional>
#include <vector>
#include "Constants.hpp"
#include "core_types.h"
#include "IEvent.hpp"
#include "BaseToolUIComponent.hpp"

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class UIManager;
			class WindowUIComponent;
			class GroupUIComponent;
			class TreeUIComponent;
		}

		namespace Tools
		{
			namespace SceneView
			{
				class BaseSceneViewEntryComponent;
			}
		}
	}
}

class SceneObject;

using namespace Bones::UI::Core;
using namespace Bones::UI::Tools::SceneView;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			/// <summary>
			/// Scene menu which contains all the data. This is usually show on left side of screen as list of all scenes and components like 
			/// buffers, framebuffers... 
			/// </summary>
			class SceneViewUIToolComponent final : public BaseToolUIComponent
			{
			public:
				// scene trees as list of various items. For example scene object such that scene -> object 1, object 2 etc... 
				TreeUIComponent* m_sceneTree = nullptr, * m_buffersTree = nullptr;

				// current state
				State m_state = State::New;

				/// <summary>
				/// Initalize. Create the components.
				/// </summary>
				void Initialize();

				/// <summary>
				/// Destroy single component.
				/// </summary>
				void DestroyComponent(BaseToolUIComponent* cmp);

				/// <summary>
				/// Destroy everything and clear.
				/// </summary>
				void Destroy();

				~SceneViewUIToolComponent();
			protected:
				// The wrapper around nuklear window.
				WindowUIComponent* m_window = nullptr;
				// Every component that's tool component and is child. In short, every which is created
				// by calling new in this class.
				std::vector< BaseSceneViewEntryComponent*> m_viewEntryComponents;
			private:
				// handles for various engine components.
				void HandleScene();
				void HandleBuffers();

				void OnIndexBufferCreate(const Bones::IEvent& evt);
				void OnVertexBufferCreate(const Bones::IEvent& evt);
				void OnInterleavedBufferCreate(const Bones::IEvent& evt);
			};
		}
	}
}

#endif // !SCENE_MENU_H
