#include "nuklear.h"
#include "BaseUIComponent.hpp"
#include "UIManager.hpp"

using namespace Bones::UI::Core;

BaseUIComponent::BaseUIComponent(nk_context* ctx)
{
	m_ctx = ctx;
}

void BaseUIComponent::AddComponent(BaseUIComponent* component)
{
	m_components.push_back(component);
}

void BaseUIComponent::DestroyComponent(BaseUIComponent* component)
{
	for (size_t i = 0; i < m_components.size(); i++)
	{
		BaseUIComponent* cmp = m_components.at(i);
		if (cmp == component)
		{
			// destroy component.
			UIManager::DestroyComponent(cmp);
			m_components.erase(m_components.begin() + i);
		}
		else
		{
			// propagate further to child components.
			cmp->DestroyComponent(component);
		}
	}
}
