#include "WindowUIComponent.hpp"
#include "CheckboxUIComponent.hpp"
#include "nuklear.h"


using namespace Bones::UI::Core;

CheckboxUIComponent::CheckboxUIComponent(nk_context* ctx, WindowUIComponent* parent, string name, bool value)
	:BaseUIComponent(ctx), m_name(name), m_value(value)
{
	parent->AddComponent(this);
	m_parent = parent;
}


void CheckboxUIComponent::Update(Uint32 dt)
{
	bool prev = m_value;
	nk_layout_row_dynamic(m_ctx, UI_ROW_HEIGHT, 1);
	m_value = nk_check_label(m_ctx, m_name.c_str(), m_value);

	if (prev != m_value)
	{
		m_onChange({ *this, m_value });
	}
}

void CheckboxUIComponent::Destroy()
{
	m_parent = nullptr;
	m_state = Bones::State::Destroyed;
}

CheckboxUIComponent::~CheckboxUIComponent()
{
	Destroy();
}
