#pragma once

namespace SlackEngine
{
	namespace Core
	{
		class ComponentsManager;
	}
}

class WorldTerrainCreator
{
public:
	WorldTerrainCreator(SlackEngine::Core::ComponentsManager* input_component_manager);
	~WorldTerrainCreator() = default;
};
