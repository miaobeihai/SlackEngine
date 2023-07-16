#include "IndicesStagingBuffer.h"

#include "Memory/VulkanMemoryAllocator.h"

SlackEngines::Render::IndicesStagingBuffer::IndicesStagingBuffer(const vk::DeviceSize& buffer_size,
                                                                 const std::vector<uint32_t>* vector_data)
{
	SlackEngine::Render::VulkanMemoryAllocator::get_instance()->create_transfer_staging_buffer(buffer_size, staging_buffer_, staging_buffer_memory_);
	
	void* data;
	SlackEngine::Render::VulkanMemoryAllocator::get_instance()->map_buffer_allocation(staging_buffer_memory_, &data);
	std::memcpy(data, vector_data->data(), static_cast<size_t>(buffer_size));
	SlackEngine::Render::VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(staging_buffer_memory_);
}
