#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>
#include "../ScoreManager/ScoreManager.h"

namespace SlackEngine
{
	namespace Core
	{
		class AudioComponent3D;
		class TriggerComponent;
		class LogicManagerView;
	}
}

class Coin final : public SlackEngine::Core::SGameObject
{
private:
	//Utils
	SlackEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	SlackEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	//Mesh
	SlackEngine::Core::MeshComponent* mesh_ = nullptr;
	//Trigger
	SlackEngine::Core::TriggerComponent* box_trigger_ = nullptr;
	SlackEngine::Core::RigidBodyComponent* test_collision_object_ = nullptr;
	//Score
	ScoreManager* score_manager_ref_ = nullptr;
	//Audio
	SlackEngine::Core::AudioComponent3D* coin_sound_ = nullptr;
	bool sound_started_ = false;
public:
	Coin(SlackEngine::Core::LogicManagerView* logic_manager_ref,
	     const SlackEngine::Core::SVector3& start_pos,
	     ScoreManager* score_manager);
	~Coin() = default;

	void set_collision_test(SGameObject* obj, int index = 1);

	void game_update(float time) override;
};
