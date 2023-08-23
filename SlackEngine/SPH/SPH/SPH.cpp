

#include <iostream>
#include <string>
#include <Engine/Manager/EngineManager.h>
#include <Engine/Input/Manager/InputManager.h>
#include <Engine/LogicCore/Scene/SceneManager.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Rendering/Manager/RenderManagerView.h>
#include <Engine/LogicCore/Manager/LogicManagerView.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>

int main()
{
	short exit_value = EXIT_SUCCESS;
	SlackEngine::Manager::EngineManager* engine_manager = nullptr;
	try
	{
		engine_manager = new SlackEngine::Manager::EngineManager("SPH", 0, 1280, 720);
		SlackEngine::Render::GameWindow* game_window_ref = engine_manager->render_manager_view->get_game_window();
		game_window_ref->set_window_icon("../assets/game_icon/crate_icon.png");

		//Create the input manager
		SlackEngine::Input::InputManager* inputmanager = game_window_ref->create_window_input_manager();
		//Get the component manager
		SlackEngine::Core::ComponentsManager* component_manager_ref = engine_manager
																	  ->logic_manager_view->get_components_manager();

		//Begin gameplay
		engine_manager->start_game_loop();
		//End gameplay
	}
	catch (const std::exception &e)
	{
		std::cerr << "EXCEPTION MESSAGE-->" << e.what() << std::endl;
		exit_value = EXIT_FAILURE;
	}
	delete engine_manager;
	return exit_value;
}

