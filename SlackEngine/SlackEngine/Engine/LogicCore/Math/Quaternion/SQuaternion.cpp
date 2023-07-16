#include <Engine/LogicCore/Math/Quaternion/SQuaternion.h>
#include <glm/gtc/quaternion.inl>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

SlackEngine::Core::SQuaternion::SQuaternion(const glm::quat input)
{
	quat_ = glm::quat(input);
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::rotate_vector(const SVector3& other) const
{
	const SVector3 q(quat_.x, quat_.y, quat_.z);
	const SVector3 t = SVector3::cross_product(q, other) * 2.f;
	const SVector3 result = other + (t * quat_.w) + SVector3::cross_product(q, t);
	return result;
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::unrotate_vector(const SVector3& other) const
{
	const SVector3 q(-quat_.x, -quat_.y, -quat_.z); // Inverse
	const SVector3 t = SVector3::cross_product(q, other) * 2.f;
	const SVector3 result = other + (t * quat_.w) + SVector3::cross_product(q, t);
	return result;
}

SlackEngine::Core::SQuaternion::SQuaternion()
{
	quat_ = glm::quat();
}

SlackEngine::Core::SQuaternion::SQuaternion(const float x, const float y, const float z, const float w)
{
	quat_ = glm::quat(w, x, y, z);
}

SlackEngine::Core::SQuaternion SlackEngine::Core::SQuaternion::identity()
{
	return SQuaternion(0, 0, 0, 1);
}

SlackEngine::Core::SQuaternion::SQuaternion(const SVector3& euler_angles)
{
	quat_ = glm::quat(radians(euler_angles.get_glm_vector()));
}

SlackEngine::Core::SQuaternion SlackEngine::Core::SQuaternion::operator*(const SQuaternion& other) const
{
	return SQuaternion(cross(quat_, other.quat_));
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_axis_x() const
{
	return rotate_vector(SVector3(1.f, 0.f, 0.f));
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_axis_y() const
{
	return rotate_vector(SVector3(0.f, 1.f, 0.f));
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_axis_z() const
{
	return rotate_vector(SVector3(0.f, 0.f, 1.f));
}

float SlackEngine::Core::SQuaternion::get_x() const
{
	return quat_.x;
}

float SlackEngine::Core::SQuaternion::get_y() const
{
	return quat_.y;
}

float SlackEngine::Core::SQuaternion::get_z() const
{
	return quat_.z;
}

float SlackEngine::Core::SQuaternion::get_w() const
{
	return quat_.w;
}

SlackEngine::Core::SQuaternion SlackEngine::Core::SQuaternion::get_inverse() const
{
	return SQuaternion(
		glm::quat_cast(glm::inverse(glm::mat4_cast(quat_)))
	);
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_forward_vector() const
{
	return get_axis_x();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_right_vector() const
{
	return get_axis_z();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::get_up_vector() const
{
	return get_axis_y();
}

SlackEngine::Core::SVector3 SlackEngine::Core::SQuaternion::to_euler_angles() const
{
	const glm::vec3 euler = eulerAngles(quat_);
	const glm::vec3 degree_v = degrees(euler);

	return SVector3(degree_v);
}

glm::quat SlackEngine::Core::SQuaternion::get_glm_quat() const
{
	return quat_;
}
