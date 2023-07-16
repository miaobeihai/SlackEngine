#include "BaseUniformBuffer.h"
#include "Memory/VulkanMemoryAllocator.h"

SlackEngine::Render::BaseUniformBuffer::~BaseUniformBuffer()
{
	for (size_t i = 0; i < uniform_buffers_.size(); i++)
	{
		VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(uniform_buffers_memory_[i]);
		VulkanMemoryAllocator::get_instance()->destroy_buffer(uniform_buffers_[i], uniform_buffers_memory_[i]);
	}
}

const std::vector<vk::Buffer>* SlackEngine::Render::BaseUniformBuffer::get_uniform_buffers() const
{
	return &uniform_buffers_;
}
