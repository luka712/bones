#pragma once

#ifndef BASE_UI_COMPONENT_H

#define BASE_UI_COMPONENT_H

#include <vector>
#include "Constants.hpp"

struct nk_context;

namespace Bones
{
	namespace UI
	{
		namespace Core
		{
			class BaseUIComponent
			{
			protected:
				nk_context* m_ctx = nullptr;
				// Default row height
				int m_rowHeight = UI_ROW_HEIGHT;

			public:
				Bones::State m_state = Bones::State::New;
				BaseUIComponent* m_parent = nullptr;
				std::vector<BaseUIComponent*> m_components;
				
				BaseUIComponent(nk_context*);
				virtual void Update(Uint32 dt) = 0;

				/// <summary>
				/// Add the child component.
				/// </summary>
				void AddComponent(BaseUIComponent* component);

				/// <summary>
				/// Destroys the child component.
				/// </summary>
				void DestroyComponent(BaseUIComponent* component);

				// TODO: add destroy
			};
		}
	}
}

#endif // !BASE_UI_COMPONENT_H
