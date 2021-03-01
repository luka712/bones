#include "ControlsComponent.hpp"
#include "sdl_include.h"

using namespace Bones::Component;

ControlsComponent::ControlsComponent()
{

}

void ControlsComponent::Initialize()
{

}

void ControlsComponent::BeforeUpdate()
{
	m_mouseMove.X = 0;
	m_mouseMove.Y = 0;
	m_mouseScroll.X = 0;
	m_mouseScroll.Y = 0;
}

void ControlsComponent::CaptureEvent(const SDL_Event& evt)
{
	auto type = evt.type;
	
	if (type == SDL_KEYDOWN)
	{
		m_pressedKeys[evt.key.keysym.sym] = true;
	}
	else if (type == SDL_KEYUP)
	{
		m_pressedKeys[evt.key.keysym.sym] = false;
	}
	else if (type == SDL_MOUSEMOTION)
	{
		m_mouseMove.X = evt.motion.xrel;
		m_mouseMove.Y = evt.motion.yrel;
	}
	else if (type == SDL_MOUSEWHEEL)
	{
		m_mouseScroll.X = evt.wheel.x;
		m_mouseScroll.Y = evt.wheel.y;
	}
	else if (type == SDL_MOUSEBUTTONDOWN)
	{
		if (evt.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseBtnPressed.Left = true;
		}
		if (evt.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseBtnPressed.Middle = true;
		}
		if (evt.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseBtnPressed.Right = true;
		}
	}
	else if (type == SDL_MOUSEBUTTONUP)
	{
		if (evt.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseBtnPressed.Left = false;
		}
		if (evt.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseBtnPressed.Middle = false;
		}
		if (evt.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseBtnPressed.Right = false;
		}
	}
}

const bool ControlsComponent::IsKeyPressed(SDL_Keycode key)  const
{
	return m_pressedKeys.find(key) != m_pressedKeys.end() && m_pressedKeys.at(key);
}