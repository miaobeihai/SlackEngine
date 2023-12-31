#include "FinishMenu.h"
#include "imgui.h"
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/Components/TriggerComponent/BoxTriggerComponent/BoxTriggerComponent.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/RigidBodyComponent.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

FinishTriggerMenu::FinishTriggerMenu(SlackEngine::Core::LogicManagerView* logic_view, Ball* player,
                                     SlackEngine::Render::GameWindow* window_ref, ScoreManager* score_manager)
	: SGameObject("Finish trigger"), player_ref_(player),
	  window_ref_(window_ref), score_manager_ref_(score_manager)
{
	set_object_location(SlackEngine::Core::SVector3(425, -20, 75));
	
	//Get component
	SlackEngine::Core::RigidBodyComponent* component = dynamic_cast<SlackEngine::Core::RigidBodyComponent*>((*
		player_ref_->get_components())[1]);
	if (component)
	{
		test_collision_object_ = component;
	}
	//Create trigger
	box_trigger_ = logic_view->get_components_manager()->create_box_trigger_component(
		SlackEngine::Core::SVector3(40, 50, 40),
		SlackEngine::Core::SVector3(425, -20, 75));
	add_component(box_trigger_);
}

void FinishTriggerMenu::game_update(float time)
{
	if (box_trigger_->test_collision(test_collision_object_))
	{
		//Set ball in trigger
		in_trigger_ = true;
		set_should_update(false);
		//Disable forces
		player_ref_->set_spawnpoint(SlackEngine::Core::SVector3(425, -0, 75));
		player_ref_->set_can_move(false);
		//Get score and time
		cache_score_ = score_manager_ref_->get_current_score();
		cache_time_ = score_manager_ref_->get_time_elapsed();
	}
}

void FinishTriggerMenu::on_gui()
{
	if (in_trigger_)
	{
		ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(0.85f); // Transparent background

		if (ImGui::Begin("Finish Menu UI Overlay", nullptr,
		                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Game Completed!");

			ImGui::Text("Congratulations!");
			const ImVec2 text_box_size = ImGui::GetItemRectSize();

			ImGui::Separator();

			ImGui::Text("Final score: %i", cache_score_);
			ImGui::Text("Time elapsed: %.1fs", cache_time_);
			const ImVec2 time_box_size = ImGui::GetItemRectSize();

			ImGui::Separator();

			if (ImGui::Button("Exit", ImVec2(text_box_size.x > time_box_size.x ? text_box_size.x : time_box_size.x,
			                                 20)))
			{
				window_ref_->close_window();
			}

			ImGui::End();
		}
	}
}
