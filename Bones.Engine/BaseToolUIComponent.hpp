#pragma once

#ifndef BASE_TOOL_UI_COMPONENT

#define BASE_TOOL_UI_COMPONENT

namespace Bones
{
	namespace UI
	{
		namespace Tools 
		{
			class BaseToolUIComponent
			{
			public:
				virtual void Initialize() = 0;
			};
		}
	}
}


#endif // !BASE_TOOL_UI_COMPONENT
