#pragma once

#include <Engine/Utility/UsefulTypes.h>

namespace SlackEngine
{
	namespace Audio
	{
		class AudioManager;
	}
}

namespace SlackEngine
{
	namespace Physics
	{
		class PhysicsManager;
	}
}

namespace SlackEngine
{
	namespace Input
	{
		class InputManager;
	}
}

namespace SlackEngine
{
	namespace Core
	{
		class LogicManagerView;
		class LogicManager;
	}
}

namespace SlackEngine
{
	namespace Render
	{
		class RenderManagerView;
		class RenderManager;
	}
}

namespace SlackEngine
{
	namespace Manager
	{
		class EngineManager
		{
		private:
			bool cleanup_done_ = false;

			game_base_info received_base_game_info_;

			Render::RenderManager* slack_render_manager_ = nullptr;
			Core::LogicManager* slack_logic_manager_ = nullptr;
			Input::InputManager* slack_input_manager_ = nullptr;
			Physics::PhysicsManager* physics_manager_ = nullptr;
			Audio::AudioManager* audio_manager_ = nullptr;

		public:
			EngineManager(const std::string& app_name = "SlackEngine Game", int app_version = 1,
			              uint32_t window_width = 800,
			              uint32_t window_height = 600, bool fullscreen = false, bool vsync = true);
			~EngineManager();

			void start_game_loop();

			Core::LogicManagerView* logic_manager_view;
			Render::RenderManagerView* render_manager_view;
		private:
			void initialize_engine();

			void initialize_render_manager(const game_base_info* game_info);
			void initialize_logic_manager();
			void initialize_physics_manager();
			void initialize_audio_manager();
			void initialize_views();

			void main_game_loop();

			//physics update frequency
			const float time_step_ = 1.0f / 120.0f;
			float accumulator_ = 0;
			void physics_update(float delta_time);

			//Gui update
			void gui_update(float time) const;

			//Audio update
			void audio_update() const;

			void cleanup_engine();
		};
	}
}
