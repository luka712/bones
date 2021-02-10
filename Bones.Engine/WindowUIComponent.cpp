#include "WindowUIComponent.hpp"
#include "nuklear.h"

using namespace Bones::UI::Core;

WindowUIComponent::WindowUIComponent(nk_context* ctx, string name, DrawRect drawRect)
	:BaseUIComponent(ctx), m_name(name), m_drawRect(drawRect)
{
}
void WindowUIComponent::Update(Uint32 dt)
{
	if (nk_begin(m_ctx, m_name.c_str(), nk_rect(m_drawRect.X, m_drawRect.Y, m_drawRect.W, m_drawRect.H),
		// NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE))
	{
		for (auto& cmp : m_components)
		{
			cmp->Update(dt);
		}
		nk_end(m_ctx);
	}

}


WindowUIComponent::~WindowUIComponent()
{
	m_components.clear();
}
