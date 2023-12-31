#include <Engine/Rendering/Camera/Camera.h>
#include <glm/gtx/quaternion.hpp>

SlackEngine::Render::Camera::Camera(const float input_min_draw_distance, const float input_max_draw_distance)
	: camera_location_(Core::SVector3(0.f, 0.f, 1.f))
{
	min_draw_distance_ = input_min_draw_distance;
	max_draw_distance_ = input_max_draw_distance;

	yaw_ = -90.0f;
	pitch_ = 0.0f;
}

void SlackEngine::Render::Camera::set_camera_location(const Core::SVector3& new_camera_location)
{
	camera_location_ = new_camera_location;

	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
}

void SlackEngine::Render::Camera::execute_camera_update()
{
	//Update view frustum
	update_frustum();
}

void SlackEngine::Render::Camera::process_mouse_movement(const float xpos, const float ypos, const bool constrain_pitch)
{
	if (first_mouse_read_)
	{
		first_mouse_read_ = false;
		last_x_ = xpos;
		last_y_ = ypos;
	}
	float xoffset = xpos - last_x_;
	float yoffset = last_y_ - ypos; // reversed since y-coordinates range from bottom to top
	last_x_ = xpos;
	last_y_ = ypos;

	xoffset *= mouse_sensivity_;
	yoffset *= mouse_sensivity_;

	yaw_ += xoffset;
	pitch_ += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrain_pitch)
	{
		if (pitch_ > 89.0f)
			pitch_ = 89.0f;
		if (pitch_ < -89.0f)
			pitch_ = -89.0f;
	}
	//Update data
	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
}

void SlackEngine::Render::Camera::update_camera_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(-pitch_));
	camera_front_ = normalize(front);
}

void SlackEngine::Render::Camera::set_mouse_sensivity(const float new_sensivity)
{
	mouse_sensivity_ = new_sensivity;
}

void SlackEngine::Render::Camera::set_min_render_distance(const float new_render_distance)
{
	min_draw_distance_ = new_render_distance;
	//Update projection matrix
	generate_projection_matrix();
}

void SlackEngine::Render::Camera::set_max_render_distance(const float new_render_distance)
{
	max_draw_distance_ = new_render_distance;
	//Update projection matrix
	generate_projection_matrix();
}

float SlackEngine::Render::Camera::get_camera_yaw() const
{
	return yaw_;
}

float SlackEngine::Render::Camera::get_camera_pitch() const
{
	return pitch_;
}

float SlackEngine::Render::Camera::get_camera_roll() const
{
	return roll_;
}

void SlackEngine::Render::Camera::set_camera_yaw(const float yaw)
{
	yaw_ = yaw;
	//Update data
	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
}

void SlackEngine::Render::Camera::set_camera_pitch(const float pitch)
{
	pitch_ = pitch;
	//Update data
	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
}

void SlackEngine::Render::Camera::set_camera_roll(const float roll)
{
	roll_ = roll;
	//Update data
	update_camera_vectors();
	//Ri-generate look matrix
	generate_look_matrix();
}

float SlackEngine::Render::Camera::get_mouse_sensivity() const
{
	return mouse_sensivity_;
}

float SlackEngine::Render::Camera::get_camera_min_draw_distance() const
{
	return min_draw_distance_;
}

float SlackEngine::Render::Camera::get_camera_max_draw_distance() const
{
	return max_draw_distance_;
}

SlackEngine::Core::SVector3 SlackEngine::Render::Camera::get_camera_front() const
{
	return Core::SVector3(camera_front_);
}

SlackEngine::Core::SVector3 SlackEngine::Render::Camera::get_camera_up() const
{
	return Core::SVector3(camera_up_);
}

SlackEngine::Core::SVector3 SlackEngine::Render::Camera::get_camera_location() const
{
	return camera_location_;
}

float SlackEngine::Render::Camera::get_camera_fov() const
{
	return fov_;
}

void SlackEngine::Render::Camera::set_camera_fov(const float fov)
{
	fov_ = fov;
	//Update projection matrix
	generate_projection_matrix();
}

float SlackEngine::Render::Camera::get_camera_aspect_ratio() const
{
	return swap_chain_extent_.width / static_cast<float>(swap_chain_extent_.height);
}

glm::mat4 SlackEngine::Render::Camera::get_camera_projection_matrix() const
{
	return projection_matrix_;
}

glm::mat4 SlackEngine::Render::Camera::get_camera_look_matrix() const
{
	return look_matrix_;
}

void SlackEngine::Render::Camera::set_swap_chain_extent(const vk::Extent2D& swap_chain_extent)
{
	swap_chain_extent_ = swap_chain_extent;
	generate_matrices();
}

void SlackEngine::Render::Camera::update_frustum()
{
	frustum_.update(projection_matrix_ * look_matrix_);
}

void SlackEngine::Render::Camera::generate_matrices()
{
	generate_projection_matrix();
	generate_look_matrix();
}

void SlackEngine::Render::Camera::generate_projection_matrix()
{
	//Perspective stuff
	projection_matrix_ = glm::perspective(glm::radians(fov_),
	                                      get_camera_aspect_ratio(),
	                                      min_draw_distance_,
	                                      max_draw_distance_);
	//Invert image for openGL style
	projection_matrix_[1][1] *= -1;
}

void SlackEngine::Render::Camera::generate_look_matrix()
{
	look_matrix_ = lookAt(camera_location_.get_glm_vector(),
	                      camera_location_.get_glm_vector() + camera_front_,
	                      camera_up_);
}

bool SlackEngine::Render::Camera::frustum_check_sphere(const glm::vec3& pos, const float radius)
{
	return frustum_.check_sphere(pos, radius);
}
