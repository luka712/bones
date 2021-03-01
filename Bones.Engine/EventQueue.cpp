#include "EventQueue.hpp"

std::unordered_map<std::string, std::vector<std::function<void(const Bones::IEvent&)>>> Bones::Events::EventQueue::m_listeners;
std::unordered_map<std::string, std::vector<Bones::IEvent>> Bones::Events::EventQueue::m_events;

void Bones::Events::EventQueue::QueueEvent(const IEvent& evt)
{
	if (m_events.count(evt.m_name) == 0)
	{
		 m_events.emplace(evt.m_name, std::vector<Bones::IEvent>());
	}
    m_events.at(evt.m_name).emplace_back(evt.m_name, evt.m_categoryFlag, evt.m_arguments);
}

void Bones::Events::EventQueue::OnEvent(std::string name, std::function<void(const Bones::IEvent&)> cb)
{
	if (m_listeners.count(name) == 0)
	{
		m_listeners.emplace(name, std::vector<std::function<void(const Bones::IEvent&)>>());
	}
	m_listeners.at(name).push_back(cb);
}

void Bones::Events::EventQueue::Update()
{
	// Go throught event map where ie [ "vertex_buffer.selected" : [ { list of listener callbacks} ] ]
	for (auto& listenerTuple : m_listeners)
	{
		// Go throught all the callbacks.
		for (auto& callback : listenerTuple.second)
		{
			// Go through events to fire
			if (m_events.count(listenerTuple.first) > 0)
			{
				for (const IEvent& evt : m_events.at(listenerTuple.first))
				{
					callback(evt);
				}

				// Clear events 
				m_events.at(listenerTuple.first).clear();
			}
		}
	}

}
