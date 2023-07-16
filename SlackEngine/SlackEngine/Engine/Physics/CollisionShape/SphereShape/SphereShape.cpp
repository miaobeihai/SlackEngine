#include <Engine/Physics/CollisionShape/SphereShape/SphereShape.h>
#include <Engine/Physics/PhysicsInclude.h>

SlackEngine::Physics::SphereShape::SphereShape(const float radius)
	: CollisionShape(new rp3d::SphereShape(radius))
{
}
