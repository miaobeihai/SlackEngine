#pragma once

#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

namespace SlackEngine
{
	namespace Core
	{
		class BoxRigidBodyComponent : public RigidBodyComponent
		{
		public:
			BoxRigidBodyComponent(Physics::RigidBody* rigidbody);
			~BoxRigidBodyComponent() = default;
		};
	}
}
