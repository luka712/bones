#pragma once
#ifndef TREE_UI_COMPONENT_H

#define TREE_UI_COMPONENT_H

#include "Constants.hpp"
#include "BaseUIComponent.hpp"
#include "UIStructs.hpp"
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class TreeUIComponent final : public BaseUIComponent
			{
			private:
				static unsigned int m_idGen;
				unsigned int m_id = 0;

				bool m_open = false;
				Uint32 m_updateEveryMS;
				Uint32 m_passedTimeSinceLastUpdate;
				ByteColor m_selectedColor = { UI_SELECTED_COLOR_R, UI_SELECTED_COLOR_G, UI_SELECTED_COLOR_B, UI_SELECTED_COLOR_A };

			public:
				string m_name;

				TreeUIComponent(nk_context*, string name);
				void Update(Uint32 dt);
				void AddComponent(BaseUIComponent* component);

				~TreeUIComponent();
			};
		}
	}
}

#endif // !TREE_UI_COMPONENT_H
