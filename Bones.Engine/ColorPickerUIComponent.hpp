#pragma once

#ifndef COLOR_PICKER_UI_COMPONENT_H

#define COLOR_PICKER_UI_COMPONENT_H

#include <string>
#include <functional>
#include "BaseUIComponent.hpp"
#include "UIStructs.hpp"

using namespace Bones::UI::Core;
using Bones::UI::Color;
using std::string;
using std::function;



namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class WindowUIComponent;

			class ColorPickerUIComponent : public BaseUIComponent
			{
			public:
				function<void(Color)> m_changed = [](Color color) -> void {};
				string m_name;
				Color m_value;
				ColorPickerUIComponent(nk_context* ctx, WindowUIComponent* parent, string name, Color colorValue);
				void Update(Uint32 dt);

				~ColorPickerUIComponent();
			};
		}
	}
}

#endif // !COLOR_PICKER_UI_COMPONENT_H
