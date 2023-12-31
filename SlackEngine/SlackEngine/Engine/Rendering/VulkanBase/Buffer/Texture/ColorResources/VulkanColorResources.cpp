

#include "VulkanColorResources.h"

#include "Buffer/Texture/Texture/BaseTexture.h"
#include "Buffer/Texture/TextureImageView/TextureImageView.h"
#include "Device/VulkanDevice.h"
#include "Memory/VulkanMemoryAllocator.h"
#include "SwapChain/VulkanSwapChain.h"

SlackEngine::Render::VulkanColorResources::VulkanColorResources(const vk::SampleCountFlagBits msaa_samples,
                                                                VulkanSwapChain* swap_chain_ref)
{
	const vk::Format color_format = swap_chain_ref->get_swap_chain_image_format();

	vk::ImageCreateInfo image_info(
		vk::ImageCreateFlags(),
		vk::ImageType::e2D,
		color_format,
		vk::Extent3D(swap_chain_ref->get_swap_chain_extent().width,
		             swap_chain_ref->get_swap_chain_extent().height, 1),
		1,
		1,
		msaa_samples,
		vk::ImageTiling::eOptimal,
		vk::ImageUsageFlagBits::eTransientAttachment |
		vk::ImageUsageFlagBits::eColorAttachment,
		vk::SharingMode::eExclusive
	);

	VulkanMemoryAllocator::get_instance()->create_texture_image(&image_info, color_image_, color_image_memory_);

	color_image_view_ = TextureImageView::create_image_view(
		&color_image_, color_format, vk::ImageAspectFlagBits::eColor, 1);

	BaseTexture::transition_image_layout(&color_image_, color_format, vk::ImageLayout::eUndefined,
	                                     vk::ImageLayout::eColorAttachmentOptimal, 1);
}


SlackEngine::Render::VulkanColorResources::~VulkanColorResources()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyImageView(color_image_view_);
	VulkanMemoryAllocator::get_instance()->destroy_image(color_image_, color_image_memory_);
}

vk::Image* SlackEngine::Render::VulkanColorResources::get_color_image()
{
	return &color_image_;
}

vk::ImageView* SlackEngine::Render::VulkanColorResources::get_color_image_view()
{
	return &color_image_view_;
}
