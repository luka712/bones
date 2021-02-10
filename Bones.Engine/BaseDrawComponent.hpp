#pragma once

class SceneObject;

namespace Bones
{
	namespace Components
	{
		namespace Draw
		{
			class BaseDrawComponent
			{
			protected:
				bool m_initialized = false;
			public:
				SceneObject* m_sceneObject;

				virtual void Initialize() = 0;
				virtual void Draw() = 0;
			};
		}
	}
}