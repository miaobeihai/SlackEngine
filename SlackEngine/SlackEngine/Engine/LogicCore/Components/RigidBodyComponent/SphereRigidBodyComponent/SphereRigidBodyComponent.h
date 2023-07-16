#pragma once

#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>

namespace SlackEngine
{
	namespace Core
	{
		class SphereRigidBodyComponent : public RigidBodyComponent
		{
		public:
			SphereRigidBodyComponent(Physics::RigidBody* rigidbody);
			~SphereRigidBodyComponent() = default;
		};
	}
}
