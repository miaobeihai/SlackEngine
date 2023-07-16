#include <Engine/LogicCore/Math/Transform/STransform.h>

SlackEngine::Core::STransform::STransform(const SVector3& position, const SVector3& rotation, const SVector3& scale)
	: position_(position), rotation_(rotation), quaternion_rotation_(rotation), scale_(scale)
{
}

SlackEngine::Core::SVector3 SlackEngine::Core::STransform::get_position() const
{
	return position_;
}

SlackEngine::Core::SVector3 SlackEngine::Core::STransform::get_rotation() const
{
	return rotation_;
}

SlackEngine::Core::SQuaternion SlackEngine::Core::STransform::get_quat_rotation() const
{
	return quaternion_rotation_;
}

SlackEngine::Core::SVector3 SlackEngine::Core::STransform::get_scale() const
{
	return scale_;
}

void SlackEngine::Core::STransform::set_position(const SVector3& new_position)
{
	position_ = new_position;
}

void SlackEngine::Core::STransform::set_rotation(const SVector3& new_rotation)
{
	quaternion_rotation_ = SQuaternion(new_rotation);
	rotation_ = quaternion_rotation_.to_euler_angles();
}

void SlackEngine::Core::STransform::set_rotation(const SQuaternion& new_rotation)
{
	quaternion_rotation_ = SQuaternion(new_rotation);
	rotation_ = quaternion_rotation_.to_euler_angles();
}

void SlackEngine::Core::STransform::set_quat_rotation(const SQuaternion& new_rotation)
{
	quaternion_rotation_ = new_rotation;
}

void SlackEngine::Core::STransform::add_rotation(const SVector3& rotation)
{
	set_rotation(quaternion_rotation_ * SQuaternion(rotation));
}

void SlackEngine::Core::STransform::set_scale(const SVector3& new_scale)
{
	scale_ = new_scale;
}
