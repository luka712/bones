#pragma once

#ifndef UTILS_H

#define UTILS_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <assert.h>
#include "IEntity.hpp"
#include "core_types.h"

using namespace Bones;

namespace Bones
{
	namespace Utils
	{
		/// <summary>
		/// Generates a name from original. If it's present in entites name is generate as "original (0)" or any other incrementing number
		/// until unique one is found.
		/// </summary>
		/// <param name="original">The original name.</param>
		/// <param name="entities">Entities to compare to</param>
		/// <returns>Unique name</returns>
		template<typename T = Bones::IEntity>
		static void GenerateName(const std::string& original, const std::vector<std::unique_ptr<T>>& entities, T& entity)
		{
			std::string name = original;

			size_t count = entities.size();

			bool taken = false;
			do
			{
				taken = false;
				for (size_t i = 0; i < count; i++)
				{
					// Do not compare with self.
					// if exists it's already taken, therefore try with new name.
					if (&entity != &*entities.at(i) && entities.at(i)->m_name == name)
					{
						taken = true;
						name = original + "(" + std::to_string(i) + ")";
						break;
					}
				}
			} while (taken);

			entity.m_name = name;
		}

		/// <summary>
		/// Convert from values that have 1 byte to value that has 4 bytes
		/// </summary>
		/// <returns>4 byte value</returns>
		template<typename TDestinationType, typename TSourceType>
		TDestinationType ConvertB8ToB32(const TSourceType& first, const TSourceType& second, const TSourceType& third, const  TSourceType& fourth)
		{
			TDestinationType v = first;
			v |= second << 8;
			v |= third << 16;
			v |= fourth << 24;
			return v;
		}

		/// <summary>
		/// Convert from values that have 1 bytes to value that has 2 bytes
		/// </summary>
		/// <returns>4 byte value</returns>
		template<typename TDestinationType, typename TSourceType>
		TDestinationType ConvertB8ToB16(const TSourceType& first, const TSourceType& second)
		{
			TDestinationType v = first;
			v |= second << 8;
			return v;
		}

		/// <summary>
		/// Convert from values that have 2 bytes to value that has 4 bytes
		/// </summary>
		/// <returns>4 byte value</returns>
		template<typename TDestinationType, typename TSourceType>
		TDestinationType ConvertB16ToB32(const TSourceType& first, const TSourceType& second)
		{
			TDestinationType v = first;
			v |= second << 16;
			return v;
		}

		/// <summary>
		/// Convert from 4 byte value to values of bytes where bytes are passed by address.
		/// </summary>
		template<typename TDestinationType, typename TSource>
		void ConvertB32ToB8(const TSource v, TDestinationType* first, TDestinationType* second, TDestinationType* third, TDestinationType* fourth)
		{
			*first |= v >> 0;
			*second |= v >> 8;
			*third |= v >> 16;
			*fourth |= v >> 24;
		}

		/// <summary>
		/// Convert from 2 byte value to values of bytes where bytes are passed by address.
		/// </summary>
		template<typename TDestinationType, typename TSource>
		void ConvertB16ToB8(const TSource v, TDestinationType* first, TDestinationType* second)
		{
			*first |= v >> 0;
			*second |= v >> 8;
		}

		/// <summary>
		/// Convert from 4 byte value to values of bytes U16 where bytes are passed by address.
		/// </summary>
		template<typename TDestinationType, typename TSource>
		void ConvertB32ToB16(const TSource v, TDestinationType* first, TDestinationType* second)
		{
			*first |= v >> 0;
			*second |= v >> 16;
		}

		/// <summary>
		/// Converts bytes to F32
		/// </summary>
		/// <returns>F32</returns>
		F32 ConvertU8ToF32(U8 first, U8 second, U8 thrid, U8 fourth);

		/// <summary>
		/// Convert arbitrary array pointer data to vector.
		/// Carefull, this does not cleanup data that's passed in.
		/// </summary>
		template<typename TDestinationType, typename TSourceType>
		static void ArrayPtrToVectorData(const TSourceType* sourceData, U64 length, std::vector<TDestinationType>& destination)
		{
			U64 nSourceBytes = sizeof(sourceData[0]);
			U64 nDestinationBytes = sizeof(TDestinationType);

			// byte diff. For example U64 can be packed in 4 U16. U16 can be packed into 2 U8 
			// Divide it for correct value -- U32 / U8 = 4
			//							   -- U32 / U16 = 2
			U64 diff = std::max(nSourceBytes, nDestinationBytes) / std::min(nSourceBytes, nDestinationBytes);

			// When pushing to lower value 
			// For example source of 0x00FF U16 needs to be passed to array of two U8 0xFF = 0x00FF >> 0 and 0x00 = 0x00FF >> 8
			if (nSourceBytes > nDestinationBytes)
			{
				for (size_t i = 0; i < length; i++)
				{
					TSourceType val = sourceData[i];

					if (nSourceBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB16ToB8<TDestinationType, TSourceType>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else if (nSourceBytes == 4 && nDestinationBytes == 1)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;
						TDestinationType c = 0;
						TDestinationType d = 0;

						ConvertB32ToB8<TDestinationType, TSourceType>(val, &a, &b, &c, &d);

						destination.push_back(a);
						destination.push_back(b);
						destination.push_back(c);
						destination.push_back(d);
					}
					else if (nSourceBytes == 4 && nDestinationBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB32ToB16<TDestinationType, TSourceType>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else
					{
						throw std::exception("not implemented");
					}
				}
			}
			// For example source of [0x00, 0xFF] U8 needs to be passed to U16 0x0000 << 0 |= 0x00 = 0x0000
			//															   U16 0x0000 << 8 |= 0x00 = 0xFF00
			else if (nSourceBytes < nDestinationBytes)
			{
				for (size_t i = 0; i < length; i += diff)
				{
					TDestinationType val = 0;

					if (nDestinationBytes == 2 && nSourceBytes == 1)
					{
						val = ConvertB8ToB16<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 1)
					{
						val = ConvertB8ToB32<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1], sourceData[i + 2], sourceData[i + 3]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 2)
					{
						val = ConvertB16ToB32<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1]);
					}
					else
					{
						throw std::exception("not implemented");
					}

					destination.push_back(val);
				}
			}
			// Same size
			else
			{
				for (U64 i = 0; i < length; i++)
				{
					destination.emplace_back(sourceData[i]);
				}
			}
		}

		/// <summary>
		/// Convert arbitrary array pointer data to vector.
		/// Carefull, this does not cleanup data that's passed in.
		/// </summary>
		template<typename TDestinationType>
		static void ArrayPtrToVectorData(const F32* sourceData, U64 count, std::vector<TDestinationType>& destination)
		{
			U64 nSourceBytes = 4;
			U64 nDestinationBytes = sizeof(TDestinationType);

			// byte diff. For example U64 can be packed in 4 U16. U16 can be packed into 2 U8 
			// Divide it for correct value -- U32 / U8 = 4
			//							   -- U32 / U16 = 2
			U64 diff = std::max(nSourceBytes, nDestinationBytes) / std::min(nSourceBytes, nDestinationBytes);

			// When pushing to lower value 
			// For example source of 0x00FF U16 needs to be passed to array of two U8 0xFF = 0x00FF >> 0 and 0x00 = 0x00FF >> 8
			if (nSourceBytes > nDestinationBytes)
			{
				for (size_t i = 0; i < count; i++)
				{
					U32 val = (F32_U32(sourceData[i])).m_asU32;

					if (nSourceBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB16ToB8<TDestinationType, U32>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else if (nSourceBytes == 4 && nDestinationBytes == 1)
					{
				
						TDestinationType a = 0;
						TDestinationType b = 0;
						TDestinationType c = 0;
						TDestinationType d = 0;

						ConvertB32ToB8<TDestinationType, U32>(val, &a, &b, &c, &d);

						destination.push_back(a);
						destination.push_back(b);
						destination.push_back(c);
						destination.push_back(d);
					}
					else if (nSourceBytes == 4 && nDestinationBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB32ToB16<TDestinationType, U32>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else
					{
						throw std::exception("not implemented");
					}
				}
			}
			// For example source of [0x00, 0xFF] U8 needs to be passed to U16 0x0000 << 0 |= 0x00 = 0x0000
			//															   U16 0x0000 << 8 |= 0x00 = 0xFF00
			else if (nSourceBytes < nDestinationBytes)
			{
				for (size_t i = 0; i < count; i += diff)
				{
					U32 val = 0;

					if (nDestinationBytes == 2 && nSourceBytes == 1)
					{
						val = ConvertB8ToB16<TDestinationType, U32>(sourceData[i], sourceData[i + 1]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 1)
					{
						val = ConvertB8ToB32<TDestinationType, U32>(sourceData[i], sourceData[i + 1], sourceData[i + 2], sourceData[i + 3]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 2)
					{
						val = ConvertB16ToB32<TDestinationType, U32>(sourceData[i], sourceData[i + 1]);
					}
					else
					{
						throw std::exception("not implemented");
					}

					destination.push_back(F32_U32(val).m_asF32);
				}
			}
		}

		/// <summary>
		/// This does not cleanup source data.
		/// Pass in any source data vector to be converted to destination type. 
		/// Destination type should be emptry, otherwise it's overwritten.
		/// </summary>
		template<typename TDestinationType, typename TSourceType>
		static void ConvertVectorData(const std::vector<TSourceType>& sourceData, std::vector<TDestinationType>& destination)
		{
			U64 nSourceBytes = sizeof(TSourceType);
			U64 nDestinationBytes = sizeof(TDestinationType);

			// byte diff. For example U64 can be packed in 4 U16. U16 can be packed into 2 U8 
			// Divide it for correct value -- U32 / U8 = 4
			//							   -- U32 / U16 = 2
			U64 diff = std::max(nSourceBytes, nDestinationBytes) / std::min(nSourceBytes, nDestinationBytes);

			// When pushing to lower value 
			// For example source of 0x00FF U16 needs to be passed to array of two U8 0xFF = 0x00FF >> 0 and 0x00 = 0x00FF >> 8
			if (nSourceBytes > nDestinationBytes)
			{
				for (size_t i = 0; i < sourceData.size(); i++)
				{
					TSourceType val = sourceData[i];

					if (nSourceBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB16ToB8<TDestinationType, TSourceType>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else if (nSourceBytes == 4 && nDestinationBytes == 1)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;
						TDestinationType c = 0;
						TDestinationType d = 0;

						ConvertB32ToB8<TDestinationType, TSourceType>(val, &a, &b, &c, &d);

						destination.push_back(a);
						destination.push_back(b);
						destination.push_back(c);
						destination.push_back(d);
					}
					else if(nSourceBytes == 4 && nDestinationBytes == 2)
					{
						TDestinationType a = 0;
						TDestinationType b = 0;

						ConvertB32ToB16<TDestinationType, TSourceType>(val, &a, &b);

						destination.push_back(a);
						destination.push_back(b);
					}
					else 
					{
						throw std::exception("not implemented");
					}
				}
			}
			// For example source of [0x00, 0xFF] U8 needs to be passed to U16 0x0000 << 0 |= 0x00 = 0x0000
			//															   U16 0x0000 << 8 |= 0x00 = 0xFF00
			else if (nSourceBytes < nDestinationBytes)
			{
				for (size_t i = 0; i < sourceData.size(); i += diff)
				{
					TDestinationType val = 0;

					if (nDestinationBytes == 2 && nSourceBytes == 1)
					{
						val = ConvertB8ToB16<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 1)
					{
						val = ConvertB8ToB32<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1], sourceData[i+2], sourceData[i+3]);
					}
					else if (nDestinationBytes == 4 && nSourceBytes == 2)
					{
						val = ConvertB16ToB32<TDestinationType, TSourceType>(sourceData[i], sourceData[i + 1]);
					}
					else
					{
						throw std::exception("not implemented");
					}

					destination.push_back(val);
				}
			}
		}
	}
}

#endif // !UTILS_H
