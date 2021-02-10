#pragma once

#ifndef UI_MANAGER_H

#define UI_MANAGER_H

#include "Constants.hpp"
#include "UIStructs.hpp"
#include <vector>
#include <string>
#include <queue>

using std::vector;
using std::string;
using Bones::UI::DrawRect;

struct nk_context;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{

			class BaseUIComponent;
			class WindowUIComponent;
			class ColorPickerUIComponent;
			class CheckboxUIComponent;
			class GroupUIComponent;
			class TreeUIComponent;
			class TextUIComponent;
			class SelectableLabelUIComponent;
			

			class UIManager
			{
			private:
				struct UpdateData {
					// 1000 = 1 sec for ui updates
					Uint32 m_updateAfter = 1000;
					// Reset after update
					Uint32 m_passedUpdateTime = 0;
				};

				static nk_context* m_ctx;
				static UpdateData m_updateData;
				static std::queue<SDL_Event> m_eventQueue;
			public:
				static vector<BaseUIComponent*> m_components;
				static vector<BaseUIComponent*> m_childComponents;

				static void Initialize(SDL_Window* win);
				static void PollEvents(SDL_Event evt);
				static void Update(Uint32 deltaTime);
				static void Draw();
				static void Destroy();

				static WindowUIComponent* CreateWindowComponent(string name, DrawRect drawRect);
				static ColorPickerUIComponent* CreateColorPickerComponent(WindowUIComponent* parent, string name, Color color);
				static CheckboxUIComponent* CreateCheckboxComponent(WindowUIComponent* parent, string name, bool value);
				static GroupUIComponent* CreateGroupComponent(WindowUIComponent* parent, string name);
				static TreeUIComponent* CreateTreeComponent(WindowUIComponent* parent, string name);
				static TextUIComponent* CreateTextComponent(WindowUIComponent* parent, string value, string label = "");

				/// <summary>
				/// Create clickable label which belongs to window component.
				/// </summary>
				static SelectableLabelUIComponent* CreateSelectableLabelComponent(WindowUIComponent* parent, const string& label);

				/// <summary>
				/// Create clickable label which belongs to tree view component.
				/// </summary>
				static SelectableLabelUIComponent* CreateSelectableLabelComponent(TreeUIComponent* parent, const string& label);

				static void DestroyComponent(BaseUIComponent* component);
			};
		}
	}
}

#endif // !UI_MANAGER_H
