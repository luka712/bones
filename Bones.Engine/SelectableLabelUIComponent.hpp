#pragma once

#ifndef CLICKABLE_LABEL_UI_COMPONENT_H

#define CLICKABLE_LABEL_UI_COMPONENT_H

#include <string>
#include <functional>
#include "Constants.hpp"
#include "BaseUIComponent.hpp"
#include "UIStructs.hpp"

using namespace Bones::UI::Core;
using std::string;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class WindowUIComponent;

			class SelectableLabelUIComponent : public BaseUIComponent
			{
			public:
				std::function<void(Bones::Event<SelectableLabelUIComponent&>)> m_onSelected;
				// Should fire only on proper click
				bool m_shouldFire = false;
				bool m_selected = false;
				ByteColor m_selectedColor;
				string m_name;
				SelectableLabelUIComponent(nk_context* ctx,  string name);
				void Update(Uint32 dt);

				~SelectableLabelUIComponent();
			};
		}
	}
}

#endif // !CLICKABLE_LABEL_UI_COMPONENT_H
