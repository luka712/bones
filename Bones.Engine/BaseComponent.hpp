#pragma once

#include "Constants.hpp"

namespace Bones
{
	namespace Component
	{
		class BaseComponent
		{
		public:
			virtual void Initialize() = 0;
			virtual void CaptureEvent(const SDL_Event& evt) {}
			virtual void BeforeUpdate() {}
			virtual void Update() {}
			virtual void AfterUpdate() {}
		};
	}
}