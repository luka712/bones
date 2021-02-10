#pragma once

#include <map>
#include "BaseModelLoader.hpp"

using namespace Bones::Loaders;

namespace Bones
{
	namespace Vendor
	{
		class BlyObjLoader : public BaseModelLoader
		{
		public:
			void LoadModel(const string& filename, ModelData& data, OptionsBitField options = 0) override;
			ModelData LoadModel(const string& filename, OptionsBitField options = 0) override;
		};

	}
}

