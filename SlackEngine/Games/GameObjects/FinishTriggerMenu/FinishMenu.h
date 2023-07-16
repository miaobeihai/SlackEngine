#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"
#include "../ScoreManager/ScoreManager.h"


namespace SlackEngine
{
	namespace Core
	{
		class LogicManagerView;
		class TriggerComponent;
	}
}

namespace SlackEngine
{
	namespace Render
	{
		class GameWindow;
	}
}

class FinishTriggerMenu final : public SlackEngine::Core::SGameObject
{
private:
	//Player
	Ball* player_ref_ = nullptr;
	//Window
	SlackEngine::Render::GameWindow* window_ref_ = nullptr;
	//Trigger
	SlackEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	SlackEngine::Core::RigidBodyComponent* test_collision_object_;
	//Score Manager
	ScoreManager* score_manager_ref_ = nullptr;

	bool in_trigger_ = false;
	int cache_score_ = 0;
	float cache_time_ = 0;
public:
	FinishTriggerMenu(SlackEngine::Core::LogicManagerView* logic_view,
	                  Ball* player,
	                  SlackEngine::Render::GameWindow* window_ref,
	                  ScoreManager* score_manager);
	~FinishTriggerMenu() = default;

	void game_update(float time) override;
	void on_gui() override;
};
