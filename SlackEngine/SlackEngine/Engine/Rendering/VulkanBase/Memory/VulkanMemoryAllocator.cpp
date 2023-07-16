#define VMA_IMPLEMENTATION
#include "VulkanMemoryAllocator.h"

#include "DebugLog.h"


//Init static instance reference

SlackEngine::Render::VulkanMemoryAllocator* SlackEngine::Render::VulkanMemoryAllocator::instance_ = nullptr;

//Class

void SlackEngine::Render::VulkanMemoryAllocator::init(const vk::PhysicalDevice physical_device,
                                                      const vk::Device logical_device,vk::Instance instance)
{
	VmaAllocatorCreateInfo allocator_info = {};
	allocator_info.physicalDevice = physical_device;
	allocator_info.device = logical_device;
	allocator_info.instance=instance;

	vmaCreateAllocator(&allocator_info, &allocator_);
}

SlackEngine::Render::VulkanMemoryAllocator::~VulkanMemoryAllocator()
{
	vmaDestroyAllocator(allocator_);
}

SlackEngine::Render::VulkanMemoryAllocator* SlackEngine::Render::VulkanMemoryAllocator::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanMemoryAllocator();
	}
	return instance_;
}

void SlackEngine::Render::VulkanMemoryAllocator::destroy_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc) const
{
	vmaDestroyBuffer(allocator_, buffer, buff_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::destroy_image(vk::Image& image, VmaAllocation& image_alloc) const
{
	vmaDestroyImage(allocator_, image, image_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::map_buffer_allocation(VmaAllocation& buff_alloc, void** data) const
{
	const VkResult res = vmaMapMemory(allocator_, buff_alloc, &(*data));

	if (res != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(res, "[VulkanMemoryAllocator][map_buffer_allocation] Unable to map buffer memory!");
	}
}

void SlackEngine::Render::VulkanMemoryAllocator::unmap_buffer_allocation(VmaAllocation& buff_alloc) const
{
	vmaUnmapMemory(allocator_, buff_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::flush_buffer_allocation(VmaAllocation& buff_alloc,
                                                                         const vk::DeviceSize size,
                                                                         const vk::DeviceSize offset) const
{
	vmaFlushAllocation(allocator_, buff_alloc, offset, size);
}

void SlackEngine::Render::VulkanMemoryAllocator::bind_buffer(vk::Buffer& buffer, VmaAllocation& buff_alloc,
                                                             const vk::DeviceSize offset) const
{
	const VkResult res = vmaBindBufferMemory2(allocator_, buff_alloc, offset, buffer, nullptr);

	if (res != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(res, "[VulkanMemoryAllocator][bind_buffer] Unable to bind buffer memory!");
	}
}

void SlackEngine::Render::VulkanMemoryAllocator::create_generic_buffer(const vk::BufferCreateInfo* buff_info,
                                                                       const VmaAllocationCreateInfo* alloc_info,
                                                                       vk::Buffer& buffer,
                                                                       VmaAllocation& buff_alloc) const
{
	VkBuffer alloc_buffer;
	const VkBufferCreateInfo* conv_buff_info = convert_buffer_create_info(buff_info);

	const VkResult res = vmaCreateBuffer(allocator_, conv_buff_info, alloc_info, &alloc_buffer, &buff_alloc, nullptr);

	if (res != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(res, "[VulkanMemoryAllocator][create_generic_buffer] Unable to create buffer!");
	}

	//Copy the allocated buffer to the c++ bindings
	buffer = alloc_buffer;
}

void SlackEngine::Render::VulkanMemoryAllocator::create_vertex_index_buffer(const vk::BufferCreateInfo* buff_info,
                                                                            vk::Buffer& buffer,
                                                                            VmaAllocation& buff_alloc) const
{
	VmaAllocationCreateInfo alloc_info = {};
	alloc_info.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
	alloc_info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
	alloc_info.preferredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	create_generic_buffer(buff_info, &alloc_info, buffer, buff_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::create_uniform_buffer(const vk::DeviceSize size, vk::Buffer& buffer,
                                                                       VmaAllocation& buff_alloc) const
{
	const vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		size,
		vk::BufferUsageFlagBits::eUniformBuffer,
		vk::SharingMode::eExclusive
	);

	VmaAllocationCreateInfo alloc_info = {};
	alloc_info.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
	alloc_info.preferredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	create_generic_buffer(&buffer_info, &alloc_info, buffer, buff_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::create_transfer_staging_buffer(
	const vk::DeviceSize size, vk::Buffer& buffer,
	VmaAllocation& buff_alloc) const
{
	const vk::BufferCreateInfo buffer_info(
		vk::BufferCreateFlags(),
		size,
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::SharingMode::eExclusive
	);

	VmaAllocationCreateInfo alloc_info = {};
	alloc_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;
	alloc_info.preferredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	create_generic_buffer(&buffer_info, &alloc_info, buffer, buff_alloc);
}

void SlackEngine::Render::VulkanMemoryAllocator::create_generic_image(const vk::ImageCreateInfo* image_info,
                                                                      const VmaAllocationCreateInfo* alloc_info,
                                                                      vk::Image& image,
                                                                      VmaAllocation& image_alloc) const
{
	VkImage alloc_image;
	const VkImageCreateInfo* conv_image_info = convert_image_create_info(image_info);

	const VkResult res = vmaCreateImage(allocator_, conv_image_info, alloc_info, &alloc_image, &image_alloc, nullptr);

	if (res != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(res, "[VulkanMemoryAllocator][create_generic_image] Unable to create image!");
	}

	//Copy the allocated buffer to the c++ bindings
	image = alloc_image;
}

void SlackEngine::Render::VulkanMemoryAllocator::create_texture_image(const vk::ImageCreateInfo* image_info,
                                                                      vk::Image& image,
                                                                      VmaAllocation& image_alloc) const
{
	VmaAllocationCreateInfo alloc_info = {};
	alloc_info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
	alloc_info.preferredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	create_generic_image(image_info, &alloc_info, image, image_alloc);
}

const VkBufferCreateInfo* SlackEngine::Render::VulkanMemoryAllocator::convert_buffer_create_info(
	const vk::BufferCreateInfo* buffer_info)
{
	return reinterpret_cast<const VkBufferCreateInfo*>(buffer_info);
}

const VkImageCreateInfo* SlackEngine::Render::VulkanMemoryAllocator::convert_image_create_info(
	const vk::ImageCreateInfo* image_info)
{
	return reinterpret_cast<const VkImageCreateInfo*>(image_info);
}
