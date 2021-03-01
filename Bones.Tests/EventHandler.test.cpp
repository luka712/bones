
#define UNIT_TEST true 

#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "core_types.h"
#include "IEvent.hpp"
#include <EventHandler.hpp>

using namespace Bones;


namespace BonesTests
{
	TEST_CLASS(event_handler_class)
	{
	public:

		TEST_METHOD(add_remove_callback)
		{
			EventHandler<> handler;

			std::function<void(const IEvent&)> lambda = [&](const IEvent& evt) -> void {};

			handler += &lambda;


			handler -= &lambda;



			Assert::AreEqual(static_cast<size_t>(0), handler.EventsCount());

			handler.Clear();
		}

		TEST_METHOD(dupe_not_added)
		{
			EventHandler<IEvent> handler;

			std::function<void(const IEvent&)> lambda = [&](const IEvent& evt) -> void {};

			handler += &lambda;
			handler += &lambda;

			Assert::AreEqual(static_cast<size_t>(1), handler.EventsCount());

			handler.Clear();
		}

		TEST_METHOD(bind_member_function)
		{
			EventHandler<> handler;

			struct A
			{
				bool called = false;

				void Ex(const IEvent& evt)
				{
					called = true;
				}
			} a;

			handler += std::bind(&A::Ex, &a, std::placeholders::_1);

			std::unordered_map<std::string, Bones::Variant> map;
			handler.Invoke(IEvent({ "h", EventCategory::AttributeBufferEvent, map }));

			Assert::IsTrue(a.called);
		}


	};
}
