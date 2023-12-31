#pragma once

#include <vector>

#include "Queue/BaseQueue.h"

namespace SlackEngine
{
	namespace Render
	{
		class VulkanSwapChain
		{
		private:
			vk::SwapchainKHR swap_chain_;
			std::vector<vk::Image> swap_chain_images_;
			vk::Format swap_chain_image_format_;
			vk::Extent2D swap_chain_extent_;
			uint32_t image_count_ = -1;

			vk::SurfaceKHR* surface_ref_;
		public:
			struct SwapChainSupportDetails
			{
				vk::SurfaceCapabilitiesKHR capabilities;
				std::vector<vk::SurfaceFormatKHR> formats;
				std::vector<vk::PresentModeKHR> present_modes;
			};

			VulkanSwapChain(const SwapChainSupportDetails& swap_chain_support, BaseQueue::QueueFamilyIndices indices,
			                vk::SurfaceKHR* input_surface_ref, const uint32_t& width, const uint32_t& height,
			                bool vsync);
			~VulkanSwapChain();

			vk::SurfaceFormatKHR choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& available_formats);

			vk::PresentModeKHR choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& available_present_modes,
			                                            bool vsync);

			vk::Extent2D choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities, const uint32_t& width,
			                                const uint32_t& height) const;

			vk::SwapchainKHR get_swap_chain() const;

			const std::vector<vk::Image>* get_swap_chain_images_vector() const;
			vk::Format get_swap_chain_image_format() const;
			vk::Extent2D get_swap_chain_extent() const;
			uint32_t get_image_count() const;
		};
	}
}
