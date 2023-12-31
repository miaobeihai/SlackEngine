#include "CheckpointTrigger.h"
#include "imgui.h"
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/Physics/RigidBody/RigidBody.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/BoxRigidBodyComponent/BoxRigidBodyComponent.h>
#include <Engine/LogicCore/Components/TriggerComponent/BoxTriggerComponent/BoxTriggerComponent.h>

CheckpointTrigger::CheckpointTrigger(SlackEngine::Core::LogicManagerView* logic_view,
                                     Ball* player,
                                     const SlackEngine::Core::SVector3& pos)
	: SGameObject("Checkpoint game object"), player_ref_(player)
{
	set_object_location(pos);
	pos_ = pos;

	//Get component
	SlackEngine::Core::RigidBodyComponent* component = dynamic_cast<SlackEngine::Core::RigidBodyComponent*>((*
		player_ref_->get_components())[1]);
	if (component)
	{
		test_collision_object_ = component;
	}
	//Create trigger
	box_trigger_ = logic_view->get_components_manager()->create_box_trigger_component(
		SlackEngine::Core::SVector3(3, 3, 3) * 5,
		pos);

	//Create Mesh
	SlackEngine::Core::MeshComponent* mesh = logic_view->get_components_manager()->create_new_mesh_component(
		"../assets/models/SimpleCheckpoint.obj",
		{
			"../assets/textures/SimpleDarkGreyTexture.png",
			//First arrow
			"../assets/textures/SimpleGreyTexture.png",
			//First cylinder
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Center
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Second cylinder
			"../assets/textures/SimpleGreyTexture.png",
			//Third cylinder
			"../assets/textures/SimpleDarkGreyTexture.png",
			//Arrows
			"../assets/textures/SimpleDarkGreyTexture.png",
			"../assets/textures/SimpleDarkGreyTexture.png",
		}
	);
	add_component(mesh);
	mesh->set_component_scale(SlackEngine::Core::SVector3(3, 3, 3));
	mesh->set_is_static(true);

	//Main center Collider
	SlackEngine::Core::RigidBodyComponent* box_collider = logic_view
	                                                      ->get_components_manager()->create_box_rigidbody_component(
		                                                      SlackEngine::Core::SVector3(5, 0.5, 5) * 5,
		                                                      pos - SlackEngine::Core::SVector3(0, 1.5, 0), 0.f);
	box_collider->set_rigidbody_type(SlackEngine::Physics::RigidBody_Types::static_rigidbody);
	box_collider->set_bounciness(0);
	box_collider->set_friction_coefficient(1);
	add_component(box_collider, false);

	//Arrow angles Collider

	const SlackEngine::Core::SVector3 arrow_collider_size = SlackEngine::Core::SVector3(0.5, 0.05f, 0.5) * 5;

	const SlackEngine::Core::SVector3 right_angle = pos + SlackEngine::Core::SVector3(25, 1, 0);
	SlackEngine::Core::RigidBodyComponent* right_angle_collider = logic_view
	                                                              ->get_components_manager()->
	                                                              create_box_rigidbody_component(
		                                                              arrow_collider_size,
		                                                              right_angle, 0.f);
	right_angle_collider->set_rigidbody_type(SlackEngine::Physics::RigidBody_Types::static_rigidbody);
	right_angle_collider->set_bounciness(0);
	right_angle_collider->set_friction_coefficient(1);
	add_component(right_angle_collider, false);

	const SlackEngine::Core::SVector3 left_angle = pos + SlackEngine::Core::SVector3(-25, 1, 0);
	SlackEngine::Core::RigidBodyComponent* left_angle_collider = logic_view
	                                                             ->get_components_manager()->
	                                                             create_box_rigidbody_component(
		                                                             arrow_collider_size,
		                                                             left_angle, 0.f);
	left_angle_collider->set_rigidbody_type(SlackEngine::Physics::RigidBody_Types::static_rigidbody);
	left_angle_collider->set_bounciness(0);
	left_angle_collider->set_friction_coefficient(1);
	add_component(left_angle_collider, false);

	const SlackEngine::Core::SVector3 up_angle = pos + SlackEngine::Core::SVector3(0, 1, -25);
	SlackEngine::Core::RigidBodyComponent* up_angle_collider = logic_view
	                                                           ->get_components_manager()->
	                                                           create_box_rigidbody_component(
		                                                           arrow_collider_size,
		                                                           up_angle, 0.f);
	up_angle_collider->set_rigidbody_type(SlackEngine::Physics::RigidBody_Types::static_rigidbody);
	up_angle_collider->set_bounciness(0);
	up_angle_collider->set_friction_coefficient(1);
	add_component(up_angle_collider, false);

	const SlackEngine::Core::SVector3 bottom_angle = pos + SlackEngine::Core::SVector3(0, 1, 25);
	SlackEngine::Core::RigidBodyComponent* bottom_angle_collider = logic_view
	                                                               ->get_components_manager()->
	                                                               create_box_rigidbody_component(
		                                                               arrow_collider_size,
		                                                               bottom_angle, 0.f);
	bottom_angle_collider->set_rigidbody_type(SlackEngine::Physics::RigidBody_Types::static_rigidbody);
	bottom_angle_collider->set_bounciness(0);
	bottom_angle_collider->set_friction_coefficient(1);
	add_component(bottom_angle_collider, false);
}

void CheckpointTrigger::game_update(const float time)
{
	if (in_trigger_)
	{
		//Display gui timer
		timer_ += time;
		if (timer_ >= 2)
		{
			set_should_update(false);
		}
	}
	else
	{
		//Trigger check
		if (box_trigger_->test_collision(test_collision_object_))
		{
			//Set ball in trigger
			in_trigger_ = true;
			//Set spawnpoint
			player_ref_->set_spawnpoint(pos_ + SlackEngine::Core::SVector3(0, 15, 0));
		}
	}
}

void CheckpointTrigger::on_gui()
{
	if (in_trigger_ && timer_ < 2)
	{
		ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background

		//Set pos in the corner
		const float distance = 10.0f;
		const ImVec2 window_pos = ImVec2(distance, distance + 60);
		const ImVec2 window_pos_pivot = ImVec2(0, 0);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

		if (ImGui::Begin("Checkpoint notification UI Overlay", nullptr,
		                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration |
		                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
		                 ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Checkpoint activated!");

			ImGui::End();
		}
	}
}
