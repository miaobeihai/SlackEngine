#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Scene/SceneManager.h>
#include <Engine/LogicCore/Manager/LogicManager.h>

SlackEngine::Core::LogicManagerView::LogicManagerView(Render::RenderManager* input_render_manager_ref,
                                                      LogicManager* input_logic_manager_ref)
	: logic_manager_ref_(input_logic_manager_ref)
{
	component_manager_ = new ComponentsManager();
	component_manager_->set_render_manager(input_render_manager_ref);
	scene_manager_ = new SceneManager(input_render_manager_ref);
}

SlackEngine::Core::LogicManagerView::~LogicManagerView()
{
	delete component_manager_;
}

void SlackEngine::Core::LogicManagerView::set_physics_manager(Physics::PhysicsManager* physics_manager) const
{
	component_manager_->set_physics_manager(physics_manager);
}

void SlackEngine::Core::LogicManagerView::set_audio_manager(Audio::AudioManager* audio_manager) const
{
	component_manager_->set_audio_manager(audio_manager);
}

SlackEngine::Core::SGameObject* SlackEngine::Core::LogicManagerView::register_game_object(
	SGameObject* input_game_object) const
{
	return logic_manager_ref_->register_game_object(input_game_object);
}

void SlackEngine::Core::LogicManagerView::un_register_game_object(
	SGameObject* input_game_object) const
{
	logic_manager_ref_->un_register_game_object(input_game_object);
}

void SlackEngine::Core::LogicManagerView::delete_game_object(SGameObject* input_game_object) const
{
	logic_manager_ref_->delete_game_object(input_game_object);
}

SlackEngine::Core::ComponentsManager* SlackEngine::Core::LogicManagerView::get_components_manager() const
{
	return component_manager_;
}

SlackEngine::Core::SceneManager* SlackEngine::Core::LogicManagerView::get_scene_manager() const
{
	return scene_manager_;
}
