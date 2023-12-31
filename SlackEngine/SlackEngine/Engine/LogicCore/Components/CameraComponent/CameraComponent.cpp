#include <Engine/LogicCore/Components/CameraComponent/CameraComponent.h>
#include <Engine/Rendering/Camera/Camera.h>

void SlackEngine::Core::CameraComponent::set_rotation(const SVector3& rotation) const
{
	game_camera_ref_->set_camera_pitch(rotation.get_x());
	game_camera_ref_->set_camera_yaw(rotation.get_y());
	game_camera_ref_->set_camera_roll(rotation.get_z());
}

SlackEngine::Core::CameraComponent::CameraComponent(SlackEngine::Render::Camera* game_camera)
	: SComponent("CameraComponent"), game_camera_ref_(game_camera)
{
}

void SlackEngine::Core::CameraComponent::set_component_location(const SVector3& location)
{
	SComponent::set_component_location(location);
	game_camera_ref_->set_camera_location(location);
}

void SlackEngine::Core::CameraComponent::set_component_rotation(const SVector3& rotation)
{
	SComponent::set_component_rotation(rotation);
	set_rotation(rotation);
}

void SlackEngine::Core::CameraComponent::add_component_rotation(const SVector3& rotation)
{
	SComponent::add_component_rotation(rotation);
	set_rotation(get_component_rotation());
}

void SlackEngine::Core::CameraComponent::set_fov(const float fov) const
{
	game_camera_ref_->set_camera_fov(fov);
}

float SlackEngine::Core::CameraComponent::get_fov() const
{
	return game_camera_ref_->get_camera_fov();
}

void SlackEngine::Core::CameraComponent::set_min_render_distance(const float new_render_distance) const
{
	game_camera_ref_->set_min_render_distance(new_render_distance);
}

void SlackEngine::Core::CameraComponent::set_max_render_distance(const float new_render_distance) const
{
	game_camera_ref_->set_max_render_distance(new_render_distance);
}

float SlackEngine::Core::CameraComponent::get_camera_min_draw_distance() const
{
	return game_camera_ref_->get_camera_min_draw_distance();
}

float SlackEngine::Core::CameraComponent::get_camera_max_draw_distance() const
{
	return game_camera_ref_->get_camera_max_draw_distance();
}

SlackEngine::Core::SVector3 SlackEngine::Core::CameraComponent::get_camera_front() const
{
	return game_camera_ref_->get_camera_front();
}

SlackEngine::Core::SVector3 SlackEngine::Core::CameraComponent::get_camera_up() const
{
	return game_camera_ref_->get_camera_up();
}

void SlackEngine::Core::CameraComponent::process_mouse_movement(const float xpos, const float ypos,
                                                                const bool constrain_pitch)
{
	game_camera_ref_->process_mouse_movement(xpos, ypos, constrain_pitch);
	const float x_rot = game_camera_ref_->get_camera_pitch();
	const float y_rot = game_camera_ref_->get_camera_yaw();
	const float z_rot = game_camera_ref_->get_camera_roll();
	set_component_rotation(SVector3(x_rot, y_rot, z_rot));
}

void SlackEngine::Core::CameraComponent::set_mouse_sensivity(const float new_sensivity) const
{
	game_camera_ref_->set_mouse_sensivity(new_sensivity);
}

float SlackEngine::Core::CameraComponent::get_mouse_sensivity() const
{
	return game_camera_ref_->get_mouse_sensivity();
}

void SlackEngine::Core::CameraComponent::update_component_location()
{
	SComponent::update_component_location();
	game_camera_ref_->set_camera_location(get_component_location());
}

void SlackEngine::Core::CameraComponent::update_component_rotation()
{
	SComponent::update_component_rotation();
	game_camera_ref_->set_camera_location(get_component_location());
	set_rotation(get_component_rotation());
}

glm::mat4 SlackEngine::Core::CameraComponent::get_camera_projection_matrix() const
{
	return game_camera_ref_->get_camera_projection_matrix();
}

glm::mat4 SlackEngine::Core::CameraComponent::get_camera_look_matrix() const
{
	return game_camera_ref_->get_camera_look_matrix();
}
