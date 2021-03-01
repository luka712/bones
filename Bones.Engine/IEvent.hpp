#pragma once

#ifndef EVENT_H

#define EVENT_H

#include "PRINT_LOG_MACROS.h"
#include "core_types.h"

#include <string>
#include <vector>
#include <unordered_map>


namespace Bones
{
	// Event category. One can decide not to check for event based on category. Should improve speed.
	enum EventCategory : U64
	{
		None = 0UL,
		AttributeBufferEvent = 1UL << 0, // comes from attribute buffers
		EngineEvent = 1UL << 1,
		UIEvent = 1UL << 2 // for ui events
	};

	// Use macros to easily implement interface
#define EVENT_CLASS_TYPE(type) virtual EventType GetEventType() const override { return type; }

#define EVENT_CLASS_CATEGORY(category) virtual U64 GetCategoryFlags() const override { return category; }

	/// <summary>
	/// Events are data oriented, meaning all the event data needs to be deciphered.
	/// Usually event will have
	/// m_arguments -- map of all variant arguments.
	/// m_handled -- has event been handled
	/// </summary
	struct IEvent
	{
		/// <summary>
		/// Creates the event 
		/// </summary>
		/// <param name="name">The name of event.</param>
		/// <param name="categoryFlag">The category flags of event.</param>
		/// <param name="">Arguments as key value pairs</param>
		IEvent(const std::string& name, EventCategory categoryFlag, std::unordered_map<std::string, Bones::Variant> args)
			: m_name(name), m_categoryFlag(categoryFlag), m_arguments(args)
		{
			LOG_CONSTRUCTOR();
			LOG_FORMAT("Event: %s", name.c_str());
		}

		/// <summary>
		/// Creates the event 
		/// </summary>
		/// <param name="name">The name of event.</param>
		/// <param name="">Arguments as key value pairs</param>
		IEvent(const std::string& name, std::unordered_map<std::string, Bones::Variant> args)
			:m_name(name), m_arguments(args)
		{
			LOG_CONSTRUCTOR();
			LOG_FORMAT("Event: %s", name.c_str());
			m_categoryFlag = EventCategory::None;
		}

		IEvent(const std::string& name)
			: m_name(name)
		{
			LOG_CONSTRUCTOR();
			LOG_FORMAT("Event: %s", name.c_str());
			m_categoryFlag = EventCategory::None;
		}

		IEvent()
			: m_name("")
		{
			LOG_CONSTRUCTOR();
			m_categoryFlag = EventCategory::None;
		}

	/*	IEvent(const IEvent& other)
		{
			LOG_COPY_CONSTRUCTOR();
			m_name = other.m_name;
			m_categoryFlag = other.m_categoryFlag;
			m_arguments = other.m_arguments;
		}*/

		/*IEvent(IEvent&& other)
		{
			LOG_MOVE_OWNERSHIP_CONSTRUCTOR();
			m_categoryFlag = other.m_categoryFlag;
			m_name = other.m_name;
			m_arguments = other.m_arguments;
		}*/

		// -- Fields
		// all the arguments of event.
		std::unordered_map<std::string, Bones::Variant> m_arguments;

		// the event name 
		std::string m_name;

		// the event category
		EventCategory m_categoryFlag;

		/// <summary>
		/// Check if event is in certain category.
		/// </summary>
		/// <returns>bool</returns>
		bool IsInCategory(EventCategory category)
		{
			return m_categoryFlag & category;
		}
	};
}

#endif // !EVENT_H
