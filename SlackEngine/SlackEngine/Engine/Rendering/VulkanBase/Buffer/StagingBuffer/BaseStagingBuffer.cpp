


#include "BaseStagingBuffer.h"

#include "Memory/VulkanMemoryAllocator.h"

SlackEngine::Render::BaseStagingBuffer::~BaseStagingBuffer()
{
	VulkanMemoryAllocator::get_instance()->destroy_buffer(staging_buffer_, staging_buffer_memory_);
}

vk::Buffer* SlackEngine::Render::BaseStagingBuffer::get_staging_buffer()
{
	return &staging_buffer_;
}
