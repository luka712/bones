#include "SelectableLabelUIComponent.hpp"
#include "nuklear.h"
#include "Constants.hpp"

using namespace Bones::UI::Core;

SelectableLabelUIComponent::SelectableLabelUIComponent(nk_context* ctx, string name)
	:BaseUIComponent(ctx)
{
	m_name = name;
	m_selectedColor = { UI_SELECTED_COLOR_R , UI_SELECTED_COLOR_G, UI_SELECTED_COLOR_B, UI_SELECTED_COLOR_A };
}

void SelectableLabelUIComponent::Update(Uint32 dt)
{
	nk_layout_row_dynamic(m_ctx, UI_ROW_HEIGHT, 1);

	if (m_selected)
	{
		nk_label_colored_wrap(m_ctx, m_name.c_str(), { m_selectedColor.R, m_selectedColor.G, m_selectedColor.B, m_selectedColor.A });
	}
	// If not already, check if selected
	else
	{
		bool prevSelected = m_selected;
		m_selected = nk_widget_is_mouse_clicked(m_ctx, nk_buttons::NK_BUTTON_LEFT);
		// Fire if selected value has changed
		if (m_selected && !prevSelected)
		{
			// ref to this.
			m_onSelected({ *this });
		}
		nk_label_wrap(m_ctx, m_name.c_str());
	}
}

SelectableLabelUIComponent::~SelectableLabelUIComponent()
{
}
