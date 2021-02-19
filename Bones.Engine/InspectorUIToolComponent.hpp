#pragma once

#ifndef COMPONENT_MENU_H

#define COMPONENT_MENU_H

#include "Constants.hpp"
#include "core_types.h"
#include "BaseToolUIComponent.hpp"

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class WindowUIComponent;
		}

		namespace Tools
		{
			class SceneObjectInspectorComponent;
		}
	}
}

using namespace Bones::UI::Core;
using namespace Bones::UI::Tools;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			/// <summary>
			/// Component menu which shows data components.
			/// </summary>
			class InspectorUIToolComponent final : public BaseToolUIComponent
			{
			protected:
				WindowUIComponent* m_window = nullptr;
				SceneObjectInspectorComponent* m_inspectorSceneObjectComponent = nullptr;
			public:

				State m_state = State::New;
				void Initialize();
			};
		}
	}
}

#endif // !COMPONENT_MENU_H
