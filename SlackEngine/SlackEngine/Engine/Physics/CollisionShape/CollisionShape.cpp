#include <Engine/Physics/CollisionShape/CollisionShape.h>
#include <Engine/Physics/PhysicsInclude.h>

SlackEngine::Physics::CollisionShape::CollisionShape(reactphysics3d::CollisionShape* collision_shape)
	: collision_shape_(collision_shape)
{
}

SlackEngine::Physics::CollisionShape::~CollisionShape()
{
	delete collision_shape_;
}

reactphysics3d::CollisionShape* SlackEngine::Physics::CollisionShape::get_collision_shape() const
{
	return collision_shape_;
}
