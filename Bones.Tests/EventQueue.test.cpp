
#define UNIT_TEST true 

#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "core_types.h"
#include "IEvent.hpp"
#include <EventQueue.hpp>

using namespace Bones::Events;


namespace BonesTests
{
	TEST_CLASS(event_queue_class)
	{
	public:

		TEST_METHOD(add_and_process_event)
		{
			bool called = false;
			EventQueue::OnEvent("test", [&](const Bones::IEvent& event) -> void 
			{
				called = true;
			});

			EventQueue::QueueEvent({ "test" });

			EventQueue::Update();

			Assert::IsTrue(called);
		}
	};
}
