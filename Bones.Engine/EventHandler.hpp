#pragma once

#ifndef EVENT_HANDLER_H

#define EVENT_HANDLER_H

#include <unordered_map>
#include <functional>
#include <memory>
#include "IEvent.hpp"

namespace Bones
{
	/// <summary>
	/// The event handler.
	/// NOTE all events are stored as static in order to persist them, when instance is destroyed events 
	/// are still being kept. Best way to clear events is to remove events manually with -= operator.
	/// </summary>
	/// <typeparam name="TEvent">The type of event.<TEvent></typeparam>
	template<typename TEvent = IEvent>
	class EventHandler final
	{
	public:

		

		/// <summary>
		/// Adds event where event is of type IEvent or class that inherits IEvent. Returns true if added.
		/// </summary>
		bool AddEvent(std::function<void(const TEvent&)>* fn)
		{
			// go from end. Ofter event might be added and then removed. It's faster to check from end in that case.
			for (size_t i = m_events.size(); i > 0; i--)
			{
				auto& evt = m_events.at(i - 1).GetMember();
				if (&evt == fn)
				{
					// ASSERT(evt == &fn);
					LOG_FORMAT("Event already added at index: %zd. Mem adress: %p", i, evt);
					return false;
				}
			}

			// ownership is moved.
		    m_events.emplace_back(fn);

			return true;
		}

		/// <summary>
		/// Add IEvent or derived type. Returns true if added.
		/// CAUTION: this operator copies function.
		/// </summary>
		bool operator+=(std::function<void(const TEvent&)> fn)
		{
			// carefull, this here is copy.
			m_events.emplace_back(fn);

			return true;
		}

		/// <summary>
		/// Add IEvent or derived type. Returns true if added.
		/// Note when passed by reference, who ever is responsible for passing function needs 
		/// to make sure that it's not deleted before it is called. This class takes no responsibility 
		/// of lifecylce of passed function.
		/// </summary>
		bool operator+=(std::function<void(const TEvent&)>* fn)
		{
			return AddEvent(fn);
		}

		/// <summary>
		/// Returns true if removed, false otherwise.
		/// </summary>
		bool RemoveEvent(std::function<void(const TEvent&)>* fn)
		{
			// Loop from end, it should be faster in cases where event is added 
			// and to be removed at same time.
			for (size_t i = m_events.size(); i > 0; i--)
			{
				auto& evt = m_events.at(i - 1).GetMember();
				if (&evt == fn)
				{
					LOG_FORMAT("Removed event at index: %zd. Mem address: %p", i, evt);
					m_events.erase(m_events.begin() + (i - 1));
					return true;
				}
			}

			// ASSERT(true);
			LOG("Event not removed.");
			return false;
		}

		/// <summary>
		/// Returns true if removed, false otherwise.
		/// </summary>
		bool operator-=(std::function<void(const TEvent&)>& fn)
		{
			return RemoveEvent(&fn);
		}

		/// <summary>
		/// Returns true if removed, false otherwise.
		/// </summary>
		bool operator-=(std::function<void(const TEvent&)>* fn)
		{	
			return RemoveEvent(fn);
		}

		void Invoke(const IEvent& event);

		/// <summary>
		/// Gets the events count.
		/// This is count of all events as this is static class.
		/// </summary>
		const U64 EventsCount() const noexcept { return m_events.size(); }

		/// <summary>
		/// Clear the handler of all events.
		/// </summary>
		void Clear();

	private:
		/// <summary>
		/// Callback function, which keeps callbacks.
		/// Sometime callback can be passed be reference sometime by copy, this class function handles it.
		/// </summary>
		class Callback
		{
		public:
			Callback(std::function<void(const TEvent&)> member)
				: m_copy(true), m_member(member)
			{
			}

			Callback(std::function<void(const TEvent&)>* memberPtr)
				:m_copy(false), m_memberPtr(memberPtr)
			{
			}

			Callback(const Callback& other)
			{
				if (other.m_copy)
					m_member = other.m_member;
				else
					m_memberPtr = other.m_memberPtr;
			}

			Callback& operator=(const Callback& other)
			{
				if (other.m_copy)
					m_member = other.m_member;
				else
					m_memberPtr = other.m_memberPtr;

				return *this;
			}

			inline const std::function<void(const TEvent&)>& GetMember() const
			{
				if (m_copy)
				{
					return m_member;
				}
				return *m_memberPtr;
			}
		private:
			bool m_copy = false;
			std::function<void(const TEvent&)> m_member;
			std::function<void(const TEvent&)> *m_memberPtr;
		};

		std::vector<Callback> m_events;
	};
}

#endif // !EVENT_HANDLER_H
