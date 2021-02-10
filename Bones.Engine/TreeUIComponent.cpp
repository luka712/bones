#include "TreeUIComponent.hpp"
#include "nuklear.h"

using namespace Bones::UI::Core;

unsigned int TreeUIComponent::m_idGen = 0;

TreeUIComponent::TreeUIComponent(nk_context* ctx, string name)
	:BaseUIComponent(ctx)
{
	m_id = m_idGen++;
	m_name = name;
	m_updateEveryMS = UPDATE_INPUT_TIME;
	m_passedTimeSinceLastUpdate = 0;
}

void TreeUIComponent::Update(Uint32 dt)
{
	// If open add  color to background.
	if (m_open)
	{
		m_ctx->style.tab.background.data.color = { m_selectedColor.R, m_selectedColor.G, m_selectedColor.B, m_selectedColor.A };
	}
	else
	{
		m_ctx->style.tab.background.data.color =  { 0,0,0,0 };
	}
	if (nk_tree_push_id(m_ctx, NK_TREE_TAB, m_name.c_str(), NK_MINIMIZED, m_id)) {
		m_open = true;
		for (auto& cmp : m_components)
		{
			cmp->Update(dt);
		}
		nk_tree_pop(m_ctx);
	}
	else {
		m_open = false;
	}

	
}

void TreeUIComponent::AddComponent(BaseUIComponent* component)
{
	m_components.push_back(component);
}

TreeUIComponent::~TreeUIComponent()
{
	m_components.clear();
}
