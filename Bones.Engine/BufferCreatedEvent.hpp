#pragma once

// all the event fired from buffer created.

#include "Event.hpp"

#ifndef BUFFER_CREATED_EVENT_H

#define BUFFER_CREATED_EVENT_H

namespace Bones
{
	/// <summary>
	/// For buffer created events.
	/// </summary>
	template<typename TBuffer>
	struct BufferCreatedEvent : public IEvent<
	{

	};
}

#endif // !BUFFER_CREATED_EVENT_H
