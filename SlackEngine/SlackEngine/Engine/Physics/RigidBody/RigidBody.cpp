#include <Engine/Physics/RigidBody/RigidBody.h>
#include <glm/gtc/quaternion.inl>
#include <Engine/Physics/CollisionShape/CollisionShape.h>
#include <Engine/Physics/Utils/ConversionUtils.h>

SlackEngine::Physics::RigidBody::~RigidBody()
{
	delete shape_;
}

void SlackEngine::Physics::RigidBody::set_start_transform(const rp3d::Vector3& init_position,
                                                          const rp3d::Quaternion& init_orientation)
{
	transform_ = rp3d::Transform(init_position, init_orientation);
}

void SlackEngine::Physics::RigidBody::set_collision_shape(CollisionShape* shape)
{
	if (proxy_shape_)
	{
		body_->removeCollisionShape(proxy_shape_);
	}
	delete shape_;

	shape_ = shape;
	proxy_shape_ = body_->addCollisionShape(shape_->get_collision_shape(),
	                                        rp3d::Transform::identity(), get_mass());
}

void SlackEngine::Physics::RigidBody::set_mass(const float mass) const
{
	body_->setMass(mass);
}

float SlackEngine::Physics::RigidBody::get_mass() const
{
	if (body_)
	{
		return body_->getMass();
	}
	return 0;
}

void SlackEngine::Physics::RigidBody::set_type(const RigidBody_Types type) const
{
	body_->setType(static_cast<rp3d::BodyType>(type));
}

SlackEngine::Physics::RigidBody_Types SlackEngine::Physics::RigidBody::get_type() const
{
	return static_cast<RigidBody_Types>(body_->getType());
}

void SlackEngine::Physics::RigidBody::build_rigidbody(rp3d::DynamicsWorld* dynamic_world)
{
	body_ = dynamic_world->createRigidBody(transform_);
	body_->setMass(1.f);
}

void SlackEngine::Physics::RigidBody::remove_from_world(rp3d::DynamicsWorld* dynamic_world) const
{
	dynamic_world->destroyRigidBody(body_);
}

rp3d::RigidBody* SlackEngine::Physics::RigidBody::get_rigidbody() const
{
	return body_;
}

SlackEngine::Physics::CollisionShape* SlackEngine::Physics::RigidBody::get_collision_shape() const
{
	return shape_;
}

SlackEngine::Core::STransform SlackEngine::Physics::RigidBody::get_updated_transform(const float factor)
{
	const rp3d::Transform curr_transform = body_->getTransform();
	const rp3d::Transform interpolated_transform = rp3d::Transform::interpolateTransforms(
		prev_transform_,
		curr_transform,
		factor);
	Core::STransform return_tras = ConversionUtils::convert_transform(interpolated_transform);

	prev_transform_ = curr_transform;
	return return_tras;
}

void SlackEngine::Physics::RigidBody::set_new_transform(const Core::STransform& transform) const
{
	body_->setTransform(ConversionUtils::convert_transform(transform));
}

void SlackEngine::Physics::RigidBody::set_new_location(const Core::SVector3& location) const
{
	rp3d::Transform current_transform = body_->getTransform();
	current_transform.setPosition(ConversionUtils::convert_vector(location));
	body_->setTransform(current_transform);
}

float SlackEngine::Physics::RigidBody::get_bounciness() const
{
	// Get the current material of the body
	rp3d::Material& material = body_->getMaterial();

	return material.getBounciness();
}

void SlackEngine::Physics::RigidBody::set_bounciness(const float bounce_factor) const
{
	// Get the current material of the body
	rp3d::Material& material = body_->getMaterial();

	material.setBounciness(rp3d::decimal(bounce_factor));
}

float SlackEngine::Physics::RigidBody::get_friction_coefficient() const
{
	// Get the current material of the body
	rp3d::Material& material = body_->getMaterial();

	return material.getFrictionCoefficient();
}

void SlackEngine::Physics::RigidBody::set_friction_coefficient(const float coefficient) const
{
	// Get the current material of the body
	rp3d::Material& material = body_->getMaterial();

	material.setFrictionCoefficient(rp3d::decimal(coefficient));
}

bool SlackEngine::Physics::RigidBody::get_allowed_to_sleep() const
{
	return body_->isAllowedToSleep();
}

void SlackEngine::Physics::RigidBody::set_allowed_to_sleep(const bool allowed) const
{
	body_->setIsAllowedToSleep(allowed);
}

void SlackEngine::Physics::RigidBody::apply_force_to_center(const Core::SVector3& force) const
{
	body_->applyForceToCenterOfMass(ConversionUtils::convert_vector(force));
}

void SlackEngine::Physics::RigidBody::apply_torque(const Core::SVector3& force) const
{
	body_->applyTorque(ConversionUtils::convert_vector(force));
}

void SlackEngine::Physics::RigidBody::cancel_rigidbody_forces() const
{
	body_->setAngularVelocity(rp3d::Vector3(0, 0, 0));
	body_->setLinearVelocity(rp3d::Vector3(0, 0, 0));
}
