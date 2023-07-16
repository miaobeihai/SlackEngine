#pragma once

#include <Engine/Physics/CollisionShape/CollisionShape.h>

namespace SlackEngine {
	namespace Core {
		class SVector3;
	}
}

namespace SlackEngine
{
	namespace Physics
	{
		class BoxShape : public CollisionShape
		{
		public:
			BoxShape(const Core::SVector3& size);
			~BoxShape() = default;
		};
	}
}
