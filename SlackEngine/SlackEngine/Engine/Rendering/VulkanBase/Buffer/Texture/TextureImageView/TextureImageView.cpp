

#include "TextureImageView.h"

#include "DebugLog.h"
#include "Device/VulkanDevice.h"

SlackEngine::Render::TextureImageView::TextureImageView(vk::Image* texture_image, const uint32_t& mip_levels_data,
                                                        const bool iscubemap, const int layer_count)
{
	if (iscubemap)
	{
		texture_image_view_ = create_cube_map_image_view(texture_image, vk::Format::eR8G8B8A8Unorm,
		                                                 vk::ImageAspectFlagBits::eColor, mip_levels_data, layer_count);
	}
	else
	{
		texture_image_view_ = create_image_view(texture_image, vk::Format::eR8G8B8A8Unorm,
		                                        vk::ImageAspectFlagBits::eColor, mip_levels_data);
	}
}

SlackEngine::Render::TextureImageView::~TextureImageView()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyImageView(texture_image_view_);
}

vk::ImageView SlackEngine::Render::TextureImageView::create_image_view(vk::Image* image, const vk::Format format,
                                                                       const vk::ImageAspectFlags& aspect_flags,
                                                                       const uint32_t mip_levels_data)
{
	vk::ImageViewCreateInfo view_info(
		vk::ImageViewCreateFlags(),
		*image,
		vk::ImageViewType::e2D,
		format,
		vk::ComponentMapping(),
		vk::ImageSubresourceRange(aspect_flags, 0, mip_levels_data, 0, 1)
	);

	vk::ImageView image_view;

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createImageView(
		&view_info, nullptr, &image_view);
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "TextureImageView: Failed to create texture image view!");
	}

	return image_view;
}

vk::ImageView SlackEngine::Render::TextureImageView::create_cube_map_image_view(
	vk::Image* image, const vk::Format format, const vk::ImageAspectFlags& aspect_flags, const uint32_t mip_levels_data,
	const int layer_count)
{
	vk::ImageViewCreateInfo view_info(
		vk::ImageViewCreateFlags(),
		*image,
		vk::ImageViewType::eCube,
		format,
		vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB,
		                     vk::ComponentSwizzle::eA),
		vk::ImageSubresourceRange(aspect_flags, 0, mip_levels_data, 0, layer_count)
	);

	vk::ImageView image_view;

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createImageView(&view_info, nullptr, &image_view);
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "TextureImageView: Failed to create texture image view!");
	}

	return image_view;
}

vk::ImageView* SlackEngine::Render::TextureImageView::get_texture_image_view()
{
	return &texture_image_view_;
}
