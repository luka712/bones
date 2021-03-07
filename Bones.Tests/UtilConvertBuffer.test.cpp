
#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "utils.h"


namespace BonesTests
{
	

	TEST_CLASS(_convert)
	{
	public:
		TEST_METHOD(B16_to_B8_back_to_B16)
		{
			U16 s = 0x0B0A;
			U8 a = 0;
			U8 b = 0;

			Utils::ConvertB16ToB8(s, &a, &b);

			Assert::AreEqual(static_cast<U8>(0x0A), a);
			Assert::AreEqual(static_cast<U8>(0x0B), b);

			U16 r = Utils::ConvertB8ToB16<U16>(a, b);

			Assert::AreEqual(static_cast<int>(s), static_cast<int>(r));
		}

		TEST_METHOD(B32_to_B8_back_to_B32)
		{
			U32 s = 0x0D0C0B0A;
			U8 a = 0;
			U8 b = 0;
			U8 c = 0;
			U8 d = 0;

			Utils::ConvertB32ToB8(s, &a, &b, &c, &d);

			Assert::AreEqual(static_cast<U8>(0x0A), a);
			Assert::AreEqual(static_cast<U8>(0x0B), b);
			Assert::AreEqual(static_cast<U8>(0x0C), c);
			Assert::AreEqual(static_cast<U8>(0x0D), d);

			U32 r = Utils::ConvertB8ToB32<U32>(a, b,c,d);

			Assert::AreEqual(static_cast<int>(s), static_cast<int>(r));
		}

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

		TEST_METHOD(U32_ptr_array_to_U8_back_to_U32)
		{
			U32 *source = new U32[4]{ 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };

			std::vector<U8> dest;

			Utils::ArrayPtrToVectorData(source, 4, dest);

			// sizeof(U32) * 4  = 16
			Assert::AreEqual(16ULL, dest.size());

			std::vector<U32> destFinal;

			Utils::ConvertVectorData(dest, destFinal);

			Assert::AreEqual(0x000000FFU, destFinal[0]);
			Assert::AreEqual(0x0000FF00U, destFinal[1]);
			Assert::AreEqual(0x00FF0000U, destFinal[2]);
			Assert::AreEqual(0xFF000000U, destFinal[3]);
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
	};
}
