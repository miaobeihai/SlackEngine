
//Class

#include "VulkanCommandPool.h"

#include "DebugLog.h"
#include "Device/VulkanDevice.h"

void SlackEngine::Render::VulkanCommandPool::init(const BaseQueue::QueueFamilyIndices queue_family_indices,
                                                  const vk::CommandPoolCreateFlags& flags)
{
	vk::CommandPoolCreateInfo pool_info(flags, queue_family_indices.graphics_family);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createCommandPool(
		&pool_info, nullptr, &command_pool_);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "VulkanCommandPool: Failed to create command pool!");
	}
}

SlackEngine::Render::VulkanCommandPool::~VulkanCommandPool()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyCommandPool(command_pool_);
}

void SlackEngine::Render::VulkanCommandPool::reset_command_pool() const
{
	VulkanDevice::get_instance()->get_logical_device()->resetCommandPool(command_pool_, vk::CommandPoolResetFlags());
}

vk::CommandPool* SlackEngine::Render::VulkanCommandPool::get_command_pool()
{
	return &command_pool_;
}

SlackEngine::Render::VulkanCommandPool::operator vk::CommandPool() const
{
	return command_pool_;
}
