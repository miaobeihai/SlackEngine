#pragma once

#include <Engine/LogicCore/GameObject/SGameObject.h>

namespace SlackEngine
{
	namespace Core
	{
		class ComponentsManager;
		class MeshComponent;
	}
}

class Terrain final : public SlackEngine::Core::SGameObject
{
private:
	SlackEngine::Core::MeshComponent* mesh_ = nullptr;
public:
	enum class color
	{
		white,
		green,
		finish
	};

	Terrain(SlackEngine::Core::ComponentsManager* input_component_manager,
	        const SlackEngine::Core::SVector3& position,
	        const SlackEngine::Core::SVector3& scale,
	        color c = color::white);
	~Terrain() = default;

	void disable_shadows() const;
	void enable_shadows() const;
};
