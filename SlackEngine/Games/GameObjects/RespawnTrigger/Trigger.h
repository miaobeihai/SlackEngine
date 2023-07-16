#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace SlackEngine
{
	namespace Core
	{
		class ComponentsManager;
		class RigidBodyComponent;
		class TriggerComponent;
	}
}

class Trigger final : public SlackEngine::Core::SGameObject
{
private:
	//Trigger
	SlackEngine::Core::TriggerComponent* box_trigger_;
	//Object to test collision
	std::vector<SlackEngine::Core::RigidBodyComponent*> test_collision_objects_;
public:
	Trigger(SlackEngine::Core::ComponentsManager* input_component_manager);
	~Trigger() = default;

	void add_collision_test(SGameObject* obj, int index = 1);

	void game_update(float time) override;
};
