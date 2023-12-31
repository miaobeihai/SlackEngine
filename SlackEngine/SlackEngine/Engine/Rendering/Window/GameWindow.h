#pragma once

//This MUST remain here for macro definitions


#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

#include <string>

namespace SlackEngine
{
	namespace Input
	{
		class InputManager;
	}
}

namespace SlackEngine
{
	namespace Render
	{
		class GameWindow
		{
			friend class VulkanSurface;

		private:
			const uint32_t width_ = 800;
			const uint32_t height_ = 600;
			const std::string window_title_ = "SlackEngine Game";

			GLFWwindow* window_; //actual window reference
			Input::InputManager* input_ = nullptr;
		public:
			struct window_pos
			{
				int xpos, ypos;
			};

			GameWindow(uint32_t input_width = 800, uint32_t input_height = 600,
			           const std::string& input_window_title = "SlackEngine Game");
			~GameWindow();

			void initialize_window();
			void center_window(GLFWmonitor* monitor) const;

			window_pos get_window_pos() const;

			void set_window_size(int input_width, int input_height) const;
			void set_window_title(const std::string& title) const;
			void set_window_icon(const std::string& path_to_file) const;

			void close_window() const;

			Input::InputManager* create_window_input_manager();

			bool check_window_should_close() const;
		};
	}
}
