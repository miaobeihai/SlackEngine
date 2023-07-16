#include <Engine/Input/Manager/InputManager.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Utility/UsefulMethods.h>

SlackEngine::Input::scroll_status SlackEngine::Input::InputManager::scroll_status_ = scroll_status::scroll_still;

SlackEngine::Input::InputManager::InputManager(GLFWwindow* input_window_ref) : window_ref_(input_window_ref)
{
	glfwSetScrollCallback(window_ref_, scroll_callback);
}

SlackEngine::Input::InputManager::~InputManager()
{
	glfwDestroyCursor(cursor_);
}

SlackEngine::Input::mouse_location SlackEngine::Input::InputManager::get_last_mouse_location() const
{
	double x_position, y_position;
	glfwGetCursorPos(window_ref_, &x_position, &y_position);
	return {x_position, y_position};
}

void SlackEngine::Input::InputManager::set_cursor_input_mode(const cursor_mode new_mode) const
{
	glfwSetInputMode(window_ref_, GLFW_CURSOR, static_cast<int>(new_mode));
}

void SlackEngine::Input::InputManager::load_new_cursor(const std::string& path_to_file, const int xhot, const int yhot)
{
	glfwSetCursor(window_ref_, nullptr);
	glfwDestroyCursor(cursor_);

	GLFWimage icon = Utility::UsefulMethods::load_icon(path_to_file);
	cursor_ = glfwCreateCursor(&icon, xhot, yhot);

	glfwSetCursor(window_ref_, cursor_);
}

void SlackEngine::Input::InputManager::load_system_cursor(const system_cursor_shapes& new_shape)
{
	glfwSetCursor(window_ref_, nullptr);
	glfwDestroyCursor(cursor_);

	cursor_ = glfwCreateStandardCursor(static_cast<int>(new_shape));

	glfwSetCursor(window_ref_, cursor_);
}

void SlackEngine::Input::InputManager::reset_cursor_to_system_default()
{
	load_system_cursor(system_cursor_shapes::cursor_regular_arrow);
}

void SlackEngine::Input::InputManager::scroll_callback(GLFWwindow* window, double xoffset, const double yoffset)
{
	if (yoffset > 0)
	{
		scroll_status_ = scroll_status::scroll_up;
	}
	else if (yoffset < 0)
	{
		scroll_status_ = scroll_status::scroll_down;
	}
	else
	{
		scroll_status_ = scroll_status::scroll_still;
	}
}

SlackEngine::Input::button_state SlackEngine::Input::InputManager::get_keyboard_key_status(const int key_to_check) const
{
	return static_cast<button_state>(glfwGetKey(window_ref_, key_to_check));
}

bool SlackEngine::Input::InputManager::get_keyboard_key_pressed(const int key_to_check) const
{
	return get_keyboard_key_status(key_to_check) == button_state::pressed;
}

bool SlackEngine::Input::InputManager::get_keyboard_key_released(const int key_to_check) const
{
	return get_keyboard_key_status(key_to_check) == button_state::released;
}

SlackEngine::Input::button_state SlackEngine::Input::InputManager::get_mouse_button_status(
	const int button_to_check) const
{
	return static_cast<button_state>(glfwGetMouseButton(window_ref_, button_to_check));
}

bool SlackEngine::Input::InputManager::get_mouse_button_pressed(const int button_to_check) const
{
	return get_mouse_button_status(button_to_check) == button_state::pressed;
}

bool SlackEngine::Input::InputManager::get_mouse_button_released(const int button_to_check) const
{
	return get_mouse_button_status(button_to_check) == button_state::released;
}

SlackEngine::Input::scroll_status SlackEngine::Input::InputManager::get_mouse_scroll_status() const
{
	const scroll_status to_return = scroll_status_;
	scroll_status_ = scroll_status::scroll_still;
	return to_return;
}
