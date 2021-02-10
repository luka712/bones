#pragma once

#ifndef WINDOW_UI_COMPONENT_H

#define WINDOW_UI_COMPONENT_H

#include <string>
#include <vector>
#include "BaseUIComponent.hpp"
#include "UIStructs.hpp"

using namespace Bones::UI::Core;
using Bones::UI::DrawRect;
using std::string;
using std::vector;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{

			/// <summary>
			/// The window UI component
			/// </summary>
			class WindowUIComponent final : public BaseUIComponent
			{
			public:
				string m_name;
				DrawRect m_drawRect;

				WindowUIComponent(nk_context*, string name, DrawRect drawRect);
				void Update(Uint32 dt);

				~WindowUIComponent();
			};
		}
	}
}

#endif // !WINDOW_UI_COMPONENT_H
