#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace SlackEngine
{
	namespace Core
	{
		class MeshComponent;
		class RigidBodyComponent;
		class ComponentsManager;
	}
}

namespace SlackEngine
{
	namespace Input
	{
		class InputManager;
	}
}

class Ball final : public SlackEngine::Core::SGameObject
{
private:
	//Utils
	SlackEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	SlackEngine::Input::InputManager* input_manager_ref_ = nullptr;
	//Collider
	SlackEngine::Core::RigidBodyComponent* collider_ = nullptr;
	//Mesh
	SlackEngine::Core::MeshComponent* mesh_ = nullptr;
	//Object utils vars
	SlackEngine::Core::SVector3 respawn_point_;
	bool can_move_ = true;
public:
	Ball(SlackEngine::Core::ComponentsManager* input_component_manager,
	     SlackEngine::Input::InputManager* created_input_managerf);
	~Ball() = default;

	void game_update(float delta_time) override;
	void respawn() override;

	void set_can_move(bool can_move);
	bool get_can_move() const;
	void set_spawnpoint(const SlackEngine::Core::SVector3& pos);

	SlackEngine::Core::SVector3 get_rigidbody_location() const;
private:
	bool is_on_ground() const;
};
