#pragma once

#ifndef UTILS_H

#define UTILS_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
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
					TSourceType val = sourceData.at(i);

					destination.push_back(val);
					if (diff > 1)
					{
						// Shift by destination bytes. If destination is U16 shift by >> 8 * 2
						destination.push_back(val >> 8 * nDestinationBytes);
					}
					if (diff > 2)
					{
						destination.push_back(val >> 16 * nDestinationBytes);
						destination.push_back(val >> 24 * nDestinationBytes);
					}
					if (diff > 4)
					{
						destination.push_back(val >> 32 * nDestinationBytes);
						destination.push_back(val >> 40 * nDestinationBytes);
						destination.push_back(val >> 48 * nDestinationBytes);
						destination.push_back(val >> 56 * nDestinationBytes);
					}
				}
			}
			// For example source of [0x00, 0xFF] U8 needs to be passed to U16 0x0000 << 0 |= 0x00 = 0x0000
			//															   U16 0x0000 << 8 |= 0x00 = 0xFF00
			else if(nSourceBytes < nDestinationBytes)
			{
				for (size_t i = 0; i < sourceData.size(); i+= diff)
				{
					TDestinationType val = 0;

					val = sourceData.at(i);
					if (diff > 1)
					{
						// shift depends on source. If source is U16 shift by << 8 * 2 
						val |= (static_cast<TDestinationType>(sourceData.at(i + 1)) << 8 * nSourceBytes);
					}
					if (diff > 2)
					{
						val |= (static_cast<TDestinationType>(sourceData.at(i + 2)) << 16 * nSourceBytes);
						val |= (static_cast<TDestinationType>(sourceData.at(i + 3)) << 24 * nSourceBytes);
					}
					if (diff > 4)
					{
						val |= (static_cast<TDestinationType>(sourceData.at(i + 4)) << 32 * nSourceBytes);
						val |= (static_cast<TDestinationType>(sourceData.at(i + 5)) << 40 * nSourceBytes);
						val |= (static_cast<TDestinationType>(sourceData.at(i + 6)) << 48 * nSourceBytes);
						val |= (static_cast<TDestinationType>(sourceData.at(i + 7)) << 56 * nSourceBytes);
					}

					destination.push_back(val);
				}
			}
		}
	}
}

#endif // !UTILS_H
