#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <glm/mat4x4.hpp>

SlackEngine::Core::SComponent::SComponent(const std::string& component_name) : SObject(component_name)
{
}

SlackEngine::Core::SComponent::~SComponent()
{
	//Empty here
}

void SlackEngine::Core::SComponent::set_component_location(const SVector3& location)
{
	object_world_transform_.set_position(location);
	update_relative_location();
}

void SlackEngine::Core::SComponent::set_component_rotation(const SVector3& rotation)
{
	object_world_transform_.set_rotation(rotation);
	update_relative_rotation();
}

void SlackEngine::Core::SComponent::set_component_scale(const SVector3& scale)
{
	object_world_transform_.set_scale(scale);
	update_relative_scale();
}

void SlackEngine::Core::SComponent::add_component_rotation(const SVector3& rotation)
{
	object_world_transform_.add_rotation(rotation);
	update_relative_rotation();
}

void SlackEngine::Core::SComponent::update_component_location()
{
	const glm::mat4 local_m = generate_unscaled_transform_matrix(object_relative_transform_);
	const glm::mat4 father_m = generate_unscaled_transform_matrix(owner_->object_transform_);
	glm::mat4 full_m = father_m * local_m;

	const glm::vec3 pos = glm::vec3(full_m[3][0], full_m[3][1], full_m[3][2]);

	object_world_transform_.set_position(SVector3(pos));
}

void SlackEngine::Core::SComponent::update_component_rotation()
{
	object_world_transform_.set_rotation(
		owner_->object_transform_.get_quat_rotation() * object_relative_transform_.get_quat_rotation()
	);
	set_component_rotation(object_world_transform_.get_rotation());

	update_component_location();
}

void SlackEngine::Core::SComponent::update_component_scale()
{
	object_world_transform_.set_scale(owner_->object_transform_.get_scale() + object_relative_transform_.get_scale());
}

SlackEngine::Core::STransform SlackEngine::Core::SComponent::get_component_transform() const
{
	return object_world_transform_;
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_location() const
{
	return object_world_transform_.get_position();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_rotation() const
{
	return object_world_transform_.get_rotation();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_scale() const
{
	return object_world_transform_.get_scale();
}

SlackEngine::Core::SGameObject* SlackEngine::Core::SComponent::get_owner() const
{
	return owner_;
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_relative_location() const
{
	return object_relative_transform_.get_position();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_relative_rotation() const
{
	return object_relative_transform_.get_rotation();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SComponent::get_component_relative_scale() const
{
	return object_relative_transform_.get_scale();
}

void SlackEngine::Core::SComponent::update_relative_location()
{
	if (owner_)
	{
		object_relative_transform_.set_position(
			object_world_transform_.get_position() - owner_->object_transform_.get_position());
	}
}

void SlackEngine::Core::SComponent::update_relative_rotation()
{
	if (owner_)
	{
		object_relative_transform_.set_rotation(
			owner_->object_transform_.get_quat_rotation().get_inverse() * object_world_transform_.get_quat_rotation()
		);
	}
}

void SlackEngine::Core::SComponent::update_relative_scale()
{
	if (owner_)
	{
		object_relative_transform_.set_scale(
			object_world_transform_.get_scale() - owner_->object_transform_.get_scale());
	}
}
