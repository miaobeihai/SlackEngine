#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace SlackEngine
{
	namespace Core
	{
		class ComponentsManager;
		class AudioComponent;
	}
}

class Music final : public SlackEngine::Core::SGameObject
{
private:
	SlackEngine::Core::AudioComponent* audio_;
public:
	Music(SlackEngine::Core::ComponentsManager* input_component_manager);
	~Music() = default;

	void game_start() override;
};
