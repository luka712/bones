#pragma once

#ifndef CHECKBOX_UI_COMPONENT_H

#define CHECKBOX_UI_COMPONENT_H

#include <string>
#include <functional>
#include "BaseUIComponent.hpp"
#include "Constants.hpp"
#include "UIStructs.hpp"

using namespace Bones::UI::Core;
using std::string;
using std::function;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class WindowUIComponent;

			/// <summary>
			/// The checkbox ui component.
			/// </summary>
			class CheckboxUIComponent : public BaseUIComponent
			{
			public:
				Bones::State m_state = Bones::State::New;
				function<void(Bones::ChangeEvent< CheckboxUIComponent&, bool> evt)> m_onChange =
					[](Bones::ChangeEvent< CheckboxUIComponent&, bool> evt) -> void {};
				string m_name;
				bool m_value;

				CheckboxUIComponent(nk_context* ctx, WindowUIComponent* parent, string name, bool value);
				~CheckboxUIComponent();

				void Update(Uint32 dt);
				void Destroy();
				
			};
		}
	}
}

#endif // !CHECKBOX_UI_COMPONENT_H
