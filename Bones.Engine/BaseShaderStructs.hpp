#pragma once

#ifndef BASE_SHADER_STRUCTS_H

namespace Bones
{
	namespace Shaders
	{
		/// <summary>
		/// The camera locations. There is only one camera per shader instance.
		/// </summary>
		struct CameraLocations
		{
			int viewMatrixLocation = -1;
			int projectionMatrixLocation = -1;
			int eyePositionLocation = -1;
		};
	}
}

#endif // !BASE_SHADER_STRUCTS_H
