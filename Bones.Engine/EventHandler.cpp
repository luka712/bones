#include "EventHandler.hpp"

using namespace Bones;

void EventHandler<>::Invoke(const IEvent& event)
{
	for (size_t i = 0; i < m_events.size(); i++)
	{
		auto& fn = m_events.at(i).GetMember();
		fn(event);
	}
}

void EventHandler<>::Clear()
{
	m_events.clear();
}
