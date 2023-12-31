#include "VulkanSwapChain.h"
#include <algorithm>
#include "DebugLog.h"
#include "Device/VulkanDevice.h"


SlackEngine::Render::VulkanSwapChain::VulkanSwapChain(const SwapChainSupportDetails& swap_chain_support,
                                                      const BaseQueue::QueueFamilyIndices indices,
                                                      vk::SurfaceKHR* input_surface_ref, const uint32_t& width,
                                                      const uint32_t& height, const bool vsync)
	: surface_ref_(input_surface_ref)
{
	const vk::SurfaceFormatKHR surface_format = choose_swap_surface_format(swap_chain_support.formats);
	const vk::PresentModeKHR present_mode = choose_swap_present_mode(swap_chain_support.present_modes, vsync);
	const vk::Extent2D extent = choose_swap_extent(swap_chain_support.capabilities, width, height);

	//That +1 is necessary
	//See https://github.com/KhronosGroup/Vulkan-Docs/issues/909
	image_count_ = swap_chain_support.capabilities.minImageCount + 1;
	if (swap_chain_support.capabilities.maxImageCount > 0 &&
		image_count_ > swap_chain_support.capabilities.maxImageCount)
	{
		image_count_ = swap_chain_support.capabilities.maxImageCount;
	}

	vk::SwapchainCreateInfoKHR create_info(
		vk::SwapchainCreateFlagsKHR(),
		*surface_ref_,
		image_count_,
		surface_format.format,
		surface_format.colorSpace,
		extent,
		1,
		vk::ImageUsageFlagBits::eColorAttachment
	);

	uint32_t queue_family_indices[] = {
		static_cast<uint32_t>(indices.graphics_family), static_cast<uint32_t>(indices.present_family)
	};

	if (indices.graphics_family != indices.present_family)
	{
		create_info.setImageSharingMode(vk::SharingMode::eConcurrent);
		create_info.setQueueFamilyIndexCount(2);
		create_info.setPQueueFamilyIndices(queue_family_indices);
	}
	else
	{
		create_info.setImageSharingMode(vk::SharingMode::eExclusive);
	}

	create_info.setPreTransform(swap_chain_support.capabilities.currentTransform);
	create_info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
	create_info.setPresentMode(present_mode);
	create_info.setClipped(true);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createSwapchainKHR(&create_info, nullptr, &swap_chain_);
	
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "VulkanSwapChain: Failed to create swap chain!");
	}

	swap_chain_images_ = VulkanDevice::get_instance()->get_logical_device()->getSwapchainImagesKHR(swap_chain_);
	
	swap_chain_image_format_ = surface_format.format;
	swap_chain_extent_ = extent;
}

SlackEngine::Render::VulkanSwapChain::~VulkanSwapChain()
{
	VulkanDevice::get_instance()->get_logical_device()->destroySwapchainKHR(swap_chain_);
}

vk::SurfaceFormatKHR SlackEngine::Render::VulkanSwapChain::choose_swap_surface_format(
	const std::vector<vk::SurfaceFormatKHR>& available_formats)
{
	if (available_formats.size() == 1 && available_formats[0].format == vk::Format::eUndefined)
	{
		vk::SurfaceFormatKHR return_format;
		return_format.format = vk::Format::eB8G8R8A8Unorm;
		return_format.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;

		return return_format;
	}

	for (const auto& available_format : available_formats)
	{
		if (available_format.format == vk::Format::eB8G8R8A8Unorm && 
			available_format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
		{
			return available_format;
		}
	}

	return available_formats[0];
}

vk::PresentModeKHR SlackEngine::Render::VulkanSwapChain::choose_swap_present_mode(
	const std::vector<vk::PresentModeKHR>& available_present_modes, const bool vsync)
{
	vk::PresentModeKHR best_mode = vk::PresentModeKHR::eFifo;

	for (const auto& available_present_mode : available_present_modes)
	{
		if (vsync && (available_present_mode == vk::PresentModeKHR::eFifoRelaxed
			|| available_present_mode == vk::PresentModeKHR::eFifo))
		{
			return available_present_mode;
		}
		if (available_present_mode == vk::PresentModeKHR::eMailbox)
		{
			return available_present_mode;
		}
		else if (available_present_mode == vk::PresentModeKHR::eImmediate)
		{
			best_mode = available_present_mode;
		}
	}

	return best_mode;
}

vk::Extent2D SlackEngine::Render::VulkanSwapChain::choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities,
                                                                      const uint32_t& width,
                                                                      const uint32_t& height) const
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		VkExtent2D actual_extent = {width, height};

		actual_extent.width = std::max(capabilities.minImageExtent.width,
		                               std::min(capabilities.maxImageExtent.width, actual_extent.width));
		actual_extent.height = std::max(capabilities.minImageExtent.height,
		                                std::min(capabilities.maxImageExtent.height, actual_extent.height));

		return actual_extent;
	}
}

vk::SwapchainKHR SlackEngine::Render::VulkanSwapChain::get_swap_chain() const
{
	return swap_chain_;
}

const std::vector<vk::Image>* SlackEngine::Render::VulkanSwapChain::get_swap_chain_images_vector() const
{
	return &swap_chain_images_;
}

vk::Format SlackEngine::Render::VulkanSwapChain::get_swap_chain_image_format() const
{
	return swap_chain_image_format_;
}

vk::Extent2D SlackEngine::Render::VulkanSwapChain::get_swap_chain_extent() const
{
	return swap_chain_extent_;
}

uint32_t SlackEngine::Render::VulkanSwapChain::get_image_count() const
{
	return image_count_;
}
