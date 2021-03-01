#pragma once

#ifndef EVENT_QUEUE_H

#define EVENT_QUEUE_H

#include <unordered_map>
#include <functional>
#include "IEvent.hpp"

namespace Bones
{
	namespace Events
	{
		class EventQueue final 
		{
		public:
			/// <summary>
			/// Adds event to queue
			/// </summary>
			static void QueueEvent(const IEvent& event);

			/// <summary>
			/// OnEvent or event subscriber.
			/// </summary>
			/// <param name="name">The event name</param>
			/// <param name="cb">The callback which is going to be called on event.</param>
			static void OnEvent(std::string name, std::function<void(const Bones::IEvent&)> cb);

			/// <summary>
			/// The update method.
			/// </summary>
			static void Update();

		private:
			static std::unordered_map<std::string, std::vector<std::function<void(const Bones::IEvent&)>>> m_listeners;
			static std::unordered_map<std::string, std::vector<Bones::IEvent>> m_events;
		};
	}
}

#endif // !EVENT_QUEUE_H
