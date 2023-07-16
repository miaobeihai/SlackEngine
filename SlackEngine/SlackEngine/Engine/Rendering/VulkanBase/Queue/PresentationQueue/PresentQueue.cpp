

//Init static instance reference

#include "PresentQueue.h"

#include "Device/VulkanDevice.h"
SlackEngine::Render::PresentQueue* SlackEngine::Render::PresentQueue::instance_ = nullptr;

//Class

void SlackEngine::Render::PresentQueue::init(const QueueFamilyIndices indices)
{
	VulkanDevice::get_instance()->get_logical_device()->getQueue(indices.present_family, 0, &queue_);
}

SlackEngine::Render::PresentQueue* SlackEngine::Render::PresentQueue::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new PresentQueue();
	}
	return instance_;
}
