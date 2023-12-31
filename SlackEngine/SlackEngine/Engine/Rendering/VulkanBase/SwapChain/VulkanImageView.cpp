#include "VulkanImageView.h"
#include "Buffer/Texture/TextureImageView/TextureImageView.h"
#include "Device/VulkanDevice.h"

SlackEngine::Render::VulkanImageView::VulkanImageView(VulkanSwapChain* swap_chain_ref)
{
	const std::vector<vk::Image>* swap_chain_images = swap_chain_ref->get_swap_chain_images_vector();
	swap_chain_image_views_.resize(swap_chain_images->size());

	for (uint32_t i = 0; i < swap_chain_images->size(); i++)
	{
		swap_chain_image_views_[i] = TextureImageView::create_image_view(
			const_cast<vk::Image*>(&(*swap_chain_images)[i]),
			swap_chain_ref->get_swap_chain_image_format(),
			vk::ImageAspectFlagBits::eColor, 1);
	}
}

SlackEngine::Render::VulkanImageView::~VulkanImageView()
{
	for (const auto image_view : swap_chain_image_views_)
	{
		VulkanDevice::get_instance()->get_logical_device()->destroyImageView(image_view);
	}
}

const std::vector<vk::ImageView>* SlackEngine::Render::VulkanImageView::get_swap_chain_image_views_vector() const
{
	return &swap_chain_image_views_;
}
