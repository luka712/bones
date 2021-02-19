#pragma once

#ifndef UI_TOOLS_MANAGER_H

#define UI_TOOLS_MANAGER_H

#include "Constants.hpp"
#include <vector>
#include "core_types.h"

using Bones::State;
using std::vector;

namespace Bones
{
	namespace UI
	{
		namespace Tools
		{
			class BaseToolUIComponent;

			class UIToolsManager final
			{
			public:
				static State m_state;
				static vector< BaseToolUIComponent*> m_components;

				static void Initialize();
				static void Destroy();
			};
		}
	}
}

#endif // !UI_TOOLS_MANAGER_H
