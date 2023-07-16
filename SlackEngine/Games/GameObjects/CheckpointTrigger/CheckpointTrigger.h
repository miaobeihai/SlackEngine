#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../Player/Ball.h"

namespace SlackEngine
{
	namespace Core
	{
		class LogicManagerView;
		class TriggerComponent;
	}
}

class CheckpointTrigger final : public SlackEngine::Core::SGameObject
{
private:
	//Player
	Ball* player_ref_ = nullptr;
	//Trigger
	SlackEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	SlackEngine::Core::RigidBodyComponent* test_collision_object_;
	//Initial position
	SlackEngine::Core::SVector3 pos_;

	bool in_trigger_ = false;
	float timer_ = 0;
public:
	CheckpointTrigger(SlackEngine::Core::LogicManagerView* logic_view,
	                  Ball* player, const SlackEngine::Core::SVector3& pos);
	~CheckpointTrigger() = default;

	void game_update(float time) override;
	void on_gui() override;
};
