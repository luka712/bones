#pragma once
#ifndef INDEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H

#define INDEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H

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

	namespace Buffers
	{
		class IndexBuffer;
	}
}

using std::function;
using namespace Bones::UI::Core;
using Bones::Buffers::IndexBuffer;

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
				/// Index buffer label as seen in scene view.
				/// </summary>
				class IndexBufferSceneViewComponent final : public BaseSceneViewEntryComponent
				{
				private:
					SelectableLabelUIComponent* m_label;
					IndexBuffer* m_indexBuffer;

					// View component is parent view component, since this belongs to certaing view -> tree
					SceneViewUIToolComponent* m_viewParentPtr;

					// -- event listener
				public:
#pragma region EVENTS
					// std::function<void(Bones::Event<IndexBufferSceneViewComponent&> evt)> m_onSelected = [](Bones::Event<SceneObjectSceneViewComponent&>) -> void {};
#pragma endregion

					// -- members 
					Bones::State m_state = Bones::State::New;

					IndexBufferSceneViewComponent(IndexBuffer* iBuffer, SceneViewUIToolComponent* sceneViewParent);

					// -- interface
					void Initialize();
					// -- interface

					// TODO:
					void SetSelected(bool val) override {};
					bool IsSelected() override { return false; };

					~IndexBufferSceneViewComponent();
				};
			}
		}
	}
}

#endif // !INDEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H
