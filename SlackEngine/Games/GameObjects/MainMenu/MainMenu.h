#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"

namespace SlackEngine
{
	namespace Render
	{
		class GameWindow;
	}
}

namespace SlackEngine
{
	namespace Core
	{
		class LogicManagerView;
	}
}

class MainMenu final : public SlackEngine::Core::SGameObject
{
private:
	SlackEngine::Core::LogicManagerView* logic_view_ref_ = nullptr;
	Ball* player_ref_ = nullptr;
	SlackEngine::Render::GameWindow* window_ref_ = nullptr;
	SlackEngine::Input::InputManager* input_ref_ = nullptr;

	bool game_started_ = false;
	bool play_button_cursor_changed_ = false;
	bool exit_button_cursor_changed_ = false;
public:
	MainMenu(SlackEngine::Core::LogicManagerView* logic_view,
	         Ball* player,
	         SlackEngine::Render::GameWindow* window_ref,
	         SlackEngine::Input::InputManager* input_ref);
	~MainMenu() = default;
private:
	void on_gui() override;

	void set_hand_cursor() const;
	void set_arrow_cursor() const;
};
