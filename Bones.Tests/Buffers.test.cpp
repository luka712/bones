#define UNIT_TEST true 

#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Constants.hpp"
#include "BuffersManager.hpp"
#include "IndexBuffer.hpp"

void main() {}

using namespace Bones::Managers;
using namespace Bones::Buffers;

namespace BonesTests
{
	TEST_CLASS(BuffersManagerClass)
	{
	public:
		TEST_METHOD(create_index_buffer)
		{
			unsigned int data[5] = { 1,2,3,4,5 };
			IndexBuffer* iBuffer = BuffersManager::CreateIndexBuffer(data, 5);

			Assert::IsNotNull(iBuffer);

			BuffersManager::Destroy();
		}

		TEST_METHOD(create_index_buffer_on_initialized_test)
		{
			unsigned int data[5] = { 1,2,3,4,5 };
			IndexBuffer* iBuffer = BuffersManager::CreateIndexBuffer(data, 5);

			bool isInitCalled = false;
			iBuffer->m_onInitializedEventHandler += [&](const Bones::IEvent& evt) -> void
			{
				isInitCalled = true;
			};;

			iBuffer->Initialize();
			Assert::IsTrue(isInitCalled);

			BuffersManager::Destroy();
		}

		TEST_METHOD(create_index_buffer_on_initialized_test_inspect_event_ref)
		{
			unsigned int data[5] = { 1,2,3,4,5 };
			IndexBuffer* iBuffer = BuffersManager::CreateIndexBuffer(data, 5);

			bool isBufferInstance = false;
			iBuffer->m_onInitializedEventHandler += [&](const Bones::IEvent& evt) -> void
			{
				if (evt.m_arguments.count("source") > 0)
				{
					const Bones::Variant& variant = evt.m_arguments.at("source");
					Assert::IsTrue(Bones::Variant::Type::TYPE_POINTER == variant.m_type);
					IndexBuffer* fromPtr = static_cast<IndexBuffer*>(variant.m_asPointer);

					Assert::IsTrue(iBuffer == fromPtr);
				}
			};

			iBuffer->Initialize();

			BuffersManager::Destroy();
		}


	};
}
