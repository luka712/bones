#pragma once

#include <map>
#include "BaseComponent.hpp"

using namespace std;
using Bones::Component::BaseComponent;

namespace Bones
{
	namespace Component
	{
		struct MouseMove
		{
			Sint32 X, Y;
		};

		struct MouseScroll
		{
			Sint32 X, Y;
		};

		struct MouseBtnPressed
		{
			bool Left, Right, Middle;
		};

		class ControlsComponent : public BaseComponent
		{
		public:
			map<SDL_Keycode, bool> m_pressedKeys;
			MouseMove m_mouseMove;
			MouseScroll m_mouseScroll;
			MouseBtnPressed m_mouseBtnPressed;
			ControlsComponent();
			void Initialize() override;
			void CaptureEvent(const SDL_Event& evt) override;
			void BeforeUpdate() override;

			const MouseMove& GetMouseMove() const { return m_mouseMove; }
			const MouseScroll& GetMouseScroll() const { return m_mouseScroll; }
			const bool IsKeyPressed(SDL_Keycode key) const;
		};
	}
}