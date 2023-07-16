#include <Engine/LogicCore/Components/TriggerComponent/TriggerComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>
#include <Engine/Physics/CollisionBody/CollisionBody.h>
#include <Engine/Physics/RigidBody/RigidBody.h>

SlackEngine::Core::TriggerComponent::TriggerComponent(Physics::CollisionBody* collisionbody)
	: SComponent("TriggerComponent"), collisionbody_(collisionbody)
{
}

SlackEngine::Core::TriggerComponent::~TriggerComponent()
{
	delete collisionbody_;
}

void SlackEngine::Core::TriggerComponent::set_component_location(const SVector3& location)
{
	SComponent::set_component_location(location);
	collisionbody_->update_trasform(get_component_transform());
}

void SlackEngine::Core::TriggerComponent::set_component_rotation(const SVector3& rotation)
{
	SComponent::set_component_rotation(rotation);
	collisionbody_->update_trasform(get_component_transform());
}

bool SlackEngine::Core::TriggerComponent::test_collision(TriggerComponent* other) const
{
	return collisionbody_->test_collision(other->collisionbody_);
}

bool SlackEngine::Core::TriggerComponent::test_collision(RigidBodyComponent* other) const
{
	return collisionbody_->test_collision(other->rigidbody_->get_rigidbody());
}
