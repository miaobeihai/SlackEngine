#include <Engine/LogicCore/Manager/LogicManager.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>

SlackEngine::Core::LogicManager::~LogicManager()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		delete game_object;
	}
}

SlackEngine::Core::SGameObject* SlackEngine::Core::LogicManager::register_game_object(
	SGameObject* input_game_object)
{
	registered_game_objects_.push_back(input_game_object);
	return registered_game_objects_.back();
}

void SlackEngine::Core::LogicManager::un_register_game_object(SGameObject* input_game_object)
{
	const std::vector<SGameObject*>::iterator element = find(registered_game_objects_.begin(),
	                                                         registered_game_objects_.end(),
	                                                         input_game_object);
	if (element != registered_game_objects_.end())
	{
		delete_game_object(*element);
		registered_game_objects_.erase(element);
	}
}

void SlackEngine::Core::LogicManager::delete_game_object(SGameObject* input_game_object)
{
	delete input_game_object;
}

void SlackEngine::Core::LogicManager::execute_game_objects_start_event()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		game_object->game_start();
	}
}

void SlackEngine::Core::LogicManager::execute_game_objects_update_event(const float time)
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		if (game_object->get_should_update())
		{
			game_object->game_update(time);
		}
	}
}

void SlackEngine::Core::LogicManager::execute_game_objects_ongui_event()
{
	for (SGameObject* game_object : registered_game_objects_)
	{
		game_object->on_gui();
	}
}
