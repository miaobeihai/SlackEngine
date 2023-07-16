

//Init static instance reference

#include "GraphicsQueue.h"

#include "Device/VulkanDevice.h"
SlackEngine::Render::GraphicsQueue* SlackEngine::Render::GraphicsQueue::instance_ = nullptr;

//Class
void SlackEngine::Render::GraphicsQueue::init(const QueueFamilyIndices indices)
{
	VulkanDevice::get_instance()->get_logical_device()->getQueue(indices.graphics_family, 0, &queue_);
}

SlackEngine::Render::GraphicsQueue* SlackEngine::Render::GraphicsQueue::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GraphicsQueue();
	}
	return instance_;
}
