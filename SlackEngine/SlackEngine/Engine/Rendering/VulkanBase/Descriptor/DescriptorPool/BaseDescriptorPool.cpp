

#include "BaseDescriptorPool.h"

#include "Device/VulkanDevice.h"

SlackEngine::Render::BaseDescriptorPool::~BaseDescriptorPool()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyDescriptorPool(descriptor_pool_);
}

vk::DescriptorPool* SlackEngine::Render::BaseDescriptorPool::get_descriptor_pool()
{
	return &descriptor_pool_;
}
