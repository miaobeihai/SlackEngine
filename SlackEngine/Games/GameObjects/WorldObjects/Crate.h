#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace SlackEngine
{
	namespace Core
	{
		class RigidBodyComponent;
		class MeshComponent;
		class ComponentsManager;
		class LogicManagerView;
	}
}

class Crate final : public SlackEngine::Core::SGameObject
{
private:
	//Utils
	SlackEngine::Core::LogicManagerView* logic_manager_view_ = nullptr;
	SlackEngine::Core::ComponentsManager* component_manager_ref_ = nullptr;
	//Mesh
	SlackEngine::Core::MeshComponent* mesh_;
	//Collider
	SlackEngine::Core::RigidBodyComponent* box_collider_;
public:
	Crate(SlackEngine::Core::LogicManagerView* logic_manager_ref,
	      const SlackEngine::Core::SVector3& start_pos,
	      const SlackEngine::Core::SVector3& size = SlackEngine::Core::SVector3(1.5f, 1.5f, 1.5f),
	      float mass = 2.5f);
	~Crate() = default;

	void die() override;
};
