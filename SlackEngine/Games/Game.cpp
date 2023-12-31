#include <iostream>
#include <Engine/Manager/EngineManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include <Engine/LogicCore/Scene/SceneManager.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Rendering/Manager/RenderManagerView.h>
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

#include "GameObjects/Camera/GameCamera.h"
#include "GameObjects/Player/Ball.h"
#include "GameObjects/RespawnTrigger/Trigger.h"
#include "GameObjects/FinishTriggerMenu/FinishMenu.h"
#include "GameObjects/Music/Music.h"
#include "GameObjects/WorldTerrain/WorldTerrainCreator.h"
#include "GameObjects/WorldObjects/WorldObjectsCreator.h"
#include "GameObjects/MainMenu/MainMenu.h"
#include "GameObjects/ScoreManager/ScoreManager.h"

int main()
{
	short exit_value = EXIT_SUCCESS;
	SlackEngine::Manager::EngineManager* engine_manager = nullptr;
	try
	{
		//Init engine
		engine_manager = new SlackEngine::Manager::EngineManager("Example Game", 0, 1280, 720);
		SlackEngine::Render::GameWindow* game_window_ref = engine_manager->render_manager_view->get_game_window();
		game_window_ref->set_window_icon("../assets/game_icon/crate_icon.png");
		
		//Create the input manager
		SlackEngine::Input::InputManager* inputmanager = game_window_ref->create_window_input_manager();
		
		//Get the component manager
		SlackEngine::Core::ComponentsManager* component_manager_ref = engine_manager
		                                                              ->logic_manager_view->get_components_manager();
		//Set the world skybox
		SlackEngine::Core::SceneManager* scene_manager_ref = engine_manager
		                                                     ->logic_manager_view->get_scene_manager();
		scene_manager_ref->set_skybox(
			std::array<std::string, 6>{
				"../assets/skybox/stormydays_ft.png", //FRONT TEXTURE
				"../assets/skybox/stormydays_bk.png", //BACK TEXTURE
				"../assets/skybox/stormydays_up.png", //UP TEXTURE
				"../assets/skybox/stormydays_dn.png", //DOWN TEXTURE
				"../assets/skybox/stormydays_rt.png", //RIGHT TEXTURE
				"../assets/skybox/stormydays_lf.png", //LEFT TEXTURE
			}
		);
		scene_manager_ref->set_skybox_size(500);
		
		//Set sun position and look at
		scene_manager_ref->set_light_far_distance(2048.0f);
		scene_manager_ref->set_light_fov(60.f);
		scene_manager_ref->set_light_pos(SlackEngine::Core::SVector3(488.517f, 412.948f, 307.194f));
		scene_manager_ref->set_light_lookat(SlackEngine::Core::SVector3(223.693f, -36.6775f, -52.6496f));
		//Set world gravity
		component_manager_ref->set_gravity(SlackEngine::Core::SVector3(0, -50, 0));
		//Create world game objects
		//Ball - Player
		Ball* ball_game_object = new Ball(component_manager_ref, inputmanager);
		engine_manager->logic_manager_view->register_game_object(ball_game_object);
		
		//Respawn box trigger under the map
		Trigger* box_trigger = new Trigger(component_manager_ref);
		engine_manager->logic_manager_view->register_game_object(box_trigger);
		box_trigger->add_collision_test(ball_game_object);
		
		//Score manager
		ScoreManager* score_manager = new ScoreManager(ball_game_object, game_window_ref);
		engine_manager->logic_manager_view->register_game_object(score_manager);
		
		//Finish trigger
		engine_manager->logic_manager_view->register_game_object(new FinishTriggerMenu(
				engine_manager->logic_manager_view,
				ball_game_object,
				game_window_ref, score_manager)
		);
		
		//Terrain pieces
		WorldTerrainCreator* terrain_creator = new WorldTerrainCreator(component_manager_ref);
		delete terrain_creator;
		
		//Terrain objects
		WorldObjectsCreator* terrain_objects_creator = new WorldObjectsCreator(engine_manager->logic_manager_view,
		                                                                       ball_game_object,
		                                                                       score_manager);
		terrain_objects_creator->register_crates_to_trigger(box_trigger);
		delete terrain_objects_creator;
		
		//Create basic music object
		engine_manager->logic_manager_view->register_game_object(new Music(component_manager_ref));
		
		//Create the camera
		GameCamera* game_camera_ref = new GameCamera(inputmanager,
		                                             component_manager_ref,
		                                             ball_game_object);
		game_camera_ref->set_game_window_ref(game_window_ref);
		engine_manager->logic_manager_view->register_game_object(game_camera_ref);
		
		//MainMenu
		engine_manager->logic_manager_view->register_game_object(new MainMenu(
			engine_manager->logic_manager_view,
			ball_game_object, game_window_ref, inputmanager));
		//Begin gameplay
		engine_manager->start_game_loop();
		//End gameplay
	}
	catch (const std::exception& e)
	{
		std::cerr << "EXCEPTION MESSAGE-->" << e.what() << std::endl;
		exit_value = EXIT_FAILURE;
	}
	//Delete
	delete engine_manager;
	//Display error message
	if (exit_value == EXIT_FAILURE)
	{
		//Exit failure, wait to close
		std::cout << std::endl << "EXIT_FAILURE - Press to exit..." << std::endl;
		fflush(stdin);
		getchar();
	}
	else
	{
		std::cout << std::endl << "EXIT_SUCCESS" << std::endl;
	}
	//End of program
	return exit_value;
}
