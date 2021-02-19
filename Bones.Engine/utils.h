#pragma once

#ifndef UTILS_H

#define UTILS_H

#include <string>
#include <vector>
#include <memory>
#include "IEntity.hpp"

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
	}
}

#endif // !UTILS_H
