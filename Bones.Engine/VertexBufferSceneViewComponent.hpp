#pragma once
#ifndef VERTEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H

#define VERTEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H

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
		class VertexBuffer;
	}
}

using std::function;
using namespace Bones::UI::Core;
using Bones::Buffers::VertexBuffer;

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
				/// Vertex buffer label as seen in scene view.
				/// </summary>
				class VertexBufferSceneViewComponent final : public BaseSceneViewEntryComponent
				{
				public:
#pragma region EVENTS
					// std::function<void(Bones::Event<IndexBufferSceneViewComponent&> evt)> m_onSelected = [](Bones::Event<SceneObjectSceneViewComponent&>) -> void {};
#pragma endregion

					// -- members 
					Bones::State m_state = Bones::State::New;

					VertexBufferSceneViewComponent(VertexBuffer* iBuffer, SceneViewUIToolComponent* sceneViewParent);

					// -- interface
					void Initialize();
					// -- interface

					// TODO:
					void SetSelected(bool val) override {};
					bool IsSelected() override { return false; };

					~VertexBufferSceneViewComponent();
				private:
					SelectableLabelUIComponent* m_label;
					VertexBuffer* m_vertexBuffer;

					// View component is parent view component, since this belongs to certaing view -> tree
					SceneViewUIToolComponent* m_viewParentPtr;

					// -- event listener
				};
			}
		}
	}
}

#endif // !VERTEX_BUFFER_UI_SCENE_VIEW_COMPONENT_H
