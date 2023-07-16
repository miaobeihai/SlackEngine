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
		class CameraComponent;
	}
}

class GameCamera final : public SlackEngine::Core::SGameObject
{
private:
	SlackEngine::Core::CameraComponent* camera_component_ = nullptr;
	SlackEngine::Input::InputManager* input_manager_ref_ = nullptr;
	SlackEngine::Render::GameWindow* game_window_ref_ = nullptr;
	Ball* player_ref_ = nullptr;

	float camera_speed_ = 5.5f;
	float camera_multiplier_ = 10.f;
	//Free camera switch
	bool free_camera_ = false;
	bool free_camera_key_pressed_ = false;
public:
	GameCamera(SlackEngine::Input::InputManager* created_input_managerf,
	           SlackEngine::Core::ComponentsManager* components_manager,
	           Ball* player);
	~GameCamera() = default;

	void set_game_window_ref(SlackEngine::Render::GameWindow* window_ref);

	void game_start() override;
	void game_update(float time) override;
};
