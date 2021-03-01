#pragma once

#ifndef ENGINE_EVENT_H

#define ENGINE_EVENT_H

#include "sdl_include.h"

namespace Bones
{
	/// <summary>
	/// Pure interface class.
	/// </summary>
	class IOnSDLEvent
	{
	public:
		virtual void OnSDLEvent(const SDL_Event& evt) = 0;
	};

	/// <summary>
	/// Template interface class which expects implementation of interface.
	/// </summary>
	/// <typeparam name="T">Implementor</typeparam>
	template<typename T>
	class BaseOnSDLEvent : public IOnSDLEvent
	{
	public:
		void OnSDLEvent(const SDL_Event& evt)
		{
			static_cast<T*>(this)->OnSDLEvent_impl(evt);
		}
	};

	class IOnBeforeRenderFrame
	{
	public:
		virtual void OnBeforeFrameRender() = 0;
	};

	template<typename T>
	class BaseOnBeforeRenderFrame
	{
		// TODO:
		gkkdgk
	};
}

#endif // !ENGINE_EVENT_H
