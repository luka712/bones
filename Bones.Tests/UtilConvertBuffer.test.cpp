
#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "utils.h"


namespace BonesTests
{
	TEST_CLASS(buffers_convert)
	{
	public:

		TEST_METHOD(U32_to_U8_back_to_U32)
		{
			std::vector<U32> source{ 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000};

			std::vector<U8> dest;

			Utils::ConvertVectorData(source, dest);

			// sizeof(U32) * 4  = 16
			Assert::AreEqual(16ULL, dest.size());

			std::vector<U32> sourceBack;
			Utils::ConvertVectorData(dest, sourceBack);

			// 4ULL ... should return to original size.
			Assert::AreEqual(4ULL, sourceBack.size());

			for (size_t i = 0; i < source.size(); i++)
			{
				Assert::AreEqual(source.at(i), sourceBack.at(i));
			}
		}

		TEST_METHOD(U32_to_U16_back_to_U32)
		{
			std::vector<U32> source{ 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };

			std::vector<U16> dest;

			Utils::ConvertVectorData(source, dest);


			Assert::AreEqual(8ULL, dest.size());

			std::vector<U32> sourceBack;
			Utils::ConvertVectorData(dest, sourceBack);

			// 4ULL ... should return to original size.
			Assert::AreEqual(4ULL, sourceBack.size());

			for (size_t i = 0; i < source.size(); i++)
			{
				Assert::AreEqual(source.at(i), sourceBack.at(i));
			}
		}

		TEST_METHOD(U64_to_U8_back_to_U64)
		{
			std::vector<U64> source{ 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };

			std::vector<U8> dest;

			Utils::ConvertVectorData(source, dest);

			Assert::AreEqual(32ULL, dest.size());

			std::vector<U64> sourceBack;
			Utils::ConvertVectorData(dest, sourceBack);

			// 4ULL ... should return to original size.
			Assert::AreEqual(4ULL, sourceBack.size());

			for (size_t i = 0; i < source.size(); i++)
			{
				Assert::AreEqual(source.at(i), sourceBack.at(i));
			}
		}

		TEST_METHOD(U64_to_U16_back_to_U64)
		{
			std::vector<U64> source{ 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };

			std::vector<U16> dest;

			Utils::ConvertVectorData(source, dest);

			Assert::AreEqual(16ULL, dest.size());

			std::vector<U64> sourceBack;
			Utils::ConvertVectorData(dest, sourceBack);

			// 4ULL ... should return to original size.
			Assert::AreEqual(4ULL, sourceBack.size());

			for (size_t i = 0; i < source.size(); i++)
			{
				Assert::AreEqual(source.at(i), sourceBack.at(i));
			}
		}
	};
}
