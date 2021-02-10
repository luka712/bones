#pragma once

#ifndef UI_STRUCTS

#define UI_STRUCTS

namespace Bones
{
	namespace UI
	{
		struct DrawRect
		{
			int X, Y, W, H;
		};

		struct Color
		{
			float R, G, B, A;
		};

		struct ByteColor
		{
			unsigned char R, G, B, A;
		};
	}
}



#endif // !UI_STRUCTS
