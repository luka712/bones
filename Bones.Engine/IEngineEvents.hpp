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

	// -- Render
	// engine.OnBeforeRender
	// engine.Render 
	// engine.OnAfterRender

	/// <summary>
	/// OnBeforeFrameRender interface.
	/// </summary>
	class IOnBeforeRender
	{
	public:
		virtual void OnBeforeRender() = 0;
	};

	/// <summary>
	/// BaseOnBeforeRender
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class BaseOnBeforeRender : public IOnBeforeRender
	{
	public:
		void OnBeforeRender()
		{
			static_cast<T*>(this)->OnBeforeRender_impl();
		}
	};

	/// <summary>
	/// IOnAfterRender interface,
	/// </summary>
	class IOnAfterRender
	{
	public:
		virtual void OnAfterRender() = 0;
	};

	/// <summary>
	/// BaseOnAfterRender interface.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class BaseOnAfterRender : public IOnAfterRender
	{
	public:
		void OnAfterRender()
		{
			static_cast<T*>(this)->OnAfterRender_impl();
		}
	};
}

#endif // !ENGINE_EVENT_H
