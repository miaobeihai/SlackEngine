#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace SlackEngine
{
	namespace Physics
	{
		class CapsuleShape : public CollisionShape
		{
		public:
			CapsuleShape(float radius, float height);
			~CapsuleShape() = default;
		};
	}
}
