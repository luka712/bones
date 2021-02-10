#pragma once

#ifndef GROUP_UI_COMPONENT_H

#define GROUP_UI_COMPONENT_H

#include <vector>
#include <string>
#include "BaseUIComponent.hpp"

using std::vector;
using std::string;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class GroupUIComponent final : public BaseUIComponent
			{
			public:
				string m_name;

				GroupUIComponent(nk_context*, string name);
				void Update(Uint32 dt);
				void AddComponent(BaseUIComponent* component);

				~GroupUIComponent();
			};
		}
	}
}

#endif // !GROUP_UI_COMPONENT_H
