#pragma once

#ifndef TEXT_UI_COMPONENT_H

#define TEXT_UI_COMPONENT_H

#include <string>
#include <functional>
#include "Constants.hpp"
#include "BaseUIComponent.hpp"

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
			/// UI text component. Use template to redefine buffer size. 
			/// By default it's 100.
			/// </summary>
			class TextUIComponent final : public BaseUIComponent
			{
			private:
				char* m_buffer;
				short unsigned int m_length = 100;
				int m_currentLength = 0;
			public:
				function<void(Bones::ChangeEvent<TextUIComponent&, string>)> m_onChanged = [](Bones::ChangeEvent<TextUIComponent&, string> evt) -> void {};
				string m_labelName;
				string m_value;
				TextUIComponent(nk_context* ctx, BaseUIComponent* parent, string value);
				TextUIComponent(nk_context* ctx, BaseUIComponent* parent, string value, string labelName);
				void Update(Uint32 dt);

				~TextUIComponent();
			};
		}
	}
}

#endif // !COLOR_PICKER_UI_COMPONENT_H
