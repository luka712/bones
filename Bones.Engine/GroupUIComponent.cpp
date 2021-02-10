#include "GroupUIComponent.hpp"
#include "nuklear.h"

using namespace Bones::UI::Core;

Bones::UI::Core::GroupUIComponent::GroupUIComponent(nk_context* ctx, string name)
	:BaseUIComponent(ctx)
{
	m_name = name;
}

void Bones::UI::Core::GroupUIComponent::Update(Uint32 dt)
{
	nk_layout_row_dynamic(m_ctx, 30, 1);
	if (nk_group_begin_titled(m_ctx, m_name.c_str(), m_name.c_str(), NK_WINDOW_BORDER)) {
		//[... widgets ...]
		for (auto& cmp : m_components)
		{
			cmp->Update(dt);
		}
		nk_group_end(m_ctx);
	}
}

void GroupUIComponent::AddComponent(BaseUIComponent* component)
{
	m_components.push_back(component);
}

Bones::UI::Core::GroupUIComponent::~GroupUIComponent()
{
}
