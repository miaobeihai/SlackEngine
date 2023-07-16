#pragma once

#include "../RespawnTrigger/Trigger.h"
#include "../ScoreManager/ScoreManager.h"
#include <list>

namespace SlackEngine
{
	namespace Core
	{
		class LogicManagerView;
	}
}

class WorldObjectsCreator
{
private:
	void create_crate(const SlackEngine::Core::SVector3& pos);
	void create_coin(const SlackEngine::Core::SVector3& pos) const;
	void create_checkpoint(const SlackEngine::Core::SVector3& pos) const;
	//Creation methods
	void create_crates();
	void create_coins() const;
	void create_checkpoints() const;
	//List of crates, used to add them to kill trigger
	std::list<SlackEngine::Core::SGameObject*> crates_;
	//Utils
	SlackEngine::Core::LogicManagerView* logic_manager_ref_ = nullptr;
	Ball* player_ref_ = nullptr;
	ScoreManager* score_manager_ref_ = nullptr;
public:
	WorldObjectsCreator(SlackEngine::Core::LogicManagerView* logic_manager_ref,
	                    Ball* player,
	                    ScoreManager* score_manager);
	~WorldObjectsCreator() = default;

	void register_crates_to_trigger(Trigger* kill_trigger);
};
