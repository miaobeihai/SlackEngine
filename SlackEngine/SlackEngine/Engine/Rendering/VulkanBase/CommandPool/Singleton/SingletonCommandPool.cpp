
//Init static instance reference

#include "SingletonCommandPool.h"

SlackEngine::Render::VulkanCommandPool* SlackEngine::Render::SingletonCommandPool::instance_ = nullptr;

//Class

SlackEngine::Render::VulkanCommandPool* SlackEngine::Render::SingletonCommandPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SingletonCommandPool();
	}
	return instance_;
}
