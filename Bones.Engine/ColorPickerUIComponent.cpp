#include "ColorPickerUIComponent.hpp"
#include "WindowUIComponent.hpp"
#include "nuklear.h"
#include "TextUIComponent.hpp"


using namespace Bones::UI::Core;

ColorPickerUIComponent::ColorPickerUIComponent(nk_context* ctx, WindowUIComponent* parent, string name, Color colorValue)
    : BaseUIComponent(ctx), m_name(name), m_value(colorValue)
{
    parent->AddComponent(this);
    m_parent = parent;
}

ColorPickerUIComponent::~ColorPickerUIComponent()
{
    m_parent = nullptr;
}


void ColorPickerUIComponent::Update(Uint32 dt)
{
    nk_colorf bg = { m_value.R, m_value.G, m_value.B, m_value.A };
    nk_layout_row_dynamic(m_ctx, 20, 1);
    nk_label(m_ctx, m_name.c_str(), NK_TEXT_LEFT);
    nk_layout_row_dynamic(m_ctx, 25, 1);
    if (nk_combo_begin_color(m_ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(m_ctx), 400))) {
        nk_layout_row_dynamic(m_ctx, 120, 1);
        bg = nk_color_picker(m_ctx, bg, NK_RGBA);
        nk_layout_row_dynamic(m_ctx, 25, 1);
        bg.r = nk_propertyf(m_ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
        bg.g = nk_propertyf(m_ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
        bg.b = nk_propertyf(m_ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
        bg.a = nk_propertyf(m_ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
        nk_combo_end(m_ctx);

        if (bg.r != m_value.R || bg.g != m_value.G || bg.b != m_value.B || bg.a != m_value.A)
        {
            m_value = { bg.r, bg.g, bg.b, bg.a };
            m_changed(m_value);
        }
    }
}

