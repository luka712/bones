#include "TextUIComponent.hpp"
#include "nuklear.h"
#include <algorithm>

using Bones::UI::Core::TextUIComponent;

TextUIComponent::TextUIComponent(nk_context* ctx, BaseUIComponent* parent, string value)
	:BaseUIComponent(ctx)
{
	parent->AddComponent(this);
	m_parent = parent;
	m_value = value;
	m_labelName = "";
	m_buffer = new char[m_length];

	short unsigned int l = std::min(m_length, static_cast<short unsigned int>(value.size()));
	for (size_t i = 0; i < l; i++)
	{
		m_buffer[i] = m_value.at(i);
		m_currentLength = i;
	}
}
TextUIComponent::TextUIComponent(nk_context* ctx, BaseUIComponent* parent, string value, string labelName)
	:TextUIComponent(ctx, parent, value)
{
	m_labelName = labelName;
}

void TextUIComponent::Update(Uint32 dt)
{
	/* fixed widget window ratio width */
	nk_layout_row_dynamic(m_ctx, m_rowHeight * 1.5, 1);

	// Optionally draw label
	if (m_labelName != "")
		nk_label(m_ctx, m_labelName.c_str(), 0);

	nk_flags event = nk_edit_string(m_ctx, NK_EDIT_SIMPLE, m_buffer, &m_currentLength, m_length, nk_filter_ascii);
	if (event & NK_EDIT_DEACTIVATED)
	{
		m_value.assign(m_buffer, m_length);
		m_onChanged({ *this, m_value });
	}
	//nk_textedit_free(&text);

	// nk_text_wrap(m_ctx, m_value.c_str(), m_value.length());
}

TextUIComponent::~TextUIComponent()
{
	delete[]m_buffer;
}