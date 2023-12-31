#include "Crate.h"
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/Components/RigidBodyComponent/BoxRigidBodyComponent/BoxRigidBodyComponent.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>

Crate::Crate(SlackEngine::Core::LogicManagerView* logic_manager_ref,
             const SlackEngine::Core::SVector3& start_pos,
             const SlackEngine::Core::SVector3& size,
             const float mass)
	: SGameObject("Crate game object"), logic_manager_view_(logic_manager_ref),
	  component_manager_ref_(logic_manager_ref->get_components_manager())
{
	//Example code to load a crate that is not affected by sun
	//It keep the standard vertex shader, but use a different fragment shader
	/*mesh_ = component_manager_ref_->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base_shadow.vert.spv",
		"../assets/shader/compiled_shaders/shader_base_NO_shadow.frag.spv",
		"../assets/models/crate.obj",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	);*/

	//Add mesh to that GameObject
	mesh_ = component_manager_ref_->create_new_mesh_component(
		"../assets/models/crate.obj",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	);
	
	add_component(mesh_);

	box_collider_ = component_manager_ref_->create_box_rigidbody_component(
		size * 5,
		start_pos, mass);

	add_component(box_collider_);

	box_collider_->attach_to_mesh(mesh_);
	box_collider_->set_bounciness(0);
	box_collider_->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);

	//Set mesh scale
	mesh_->set_component_scale(size);
}

void Crate::die()
{
	mesh_->set_is_visible(false);
	//Delete trigger
	component_manager_ref_->destroy_rigidbody_component(box_collider_);
	//Delete mesh
	component_manager_ref_->destroy_mesh_component(mesh_);
	//Delete this
	logic_manager_view_->un_register_game_object(this);
}
