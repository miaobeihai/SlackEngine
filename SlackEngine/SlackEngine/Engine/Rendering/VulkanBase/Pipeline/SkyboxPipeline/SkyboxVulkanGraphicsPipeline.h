#pragma once
#include "Pipeline/BaseVulkanGraphicsPipeline.h"


namespace SlackEngine
{
	namespace Render
	{
		class SkyboxVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			SkyboxVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                             const vk::Extent2D& swap_chain_extent,
			                             vk::DescriptorSetLayout* descriptor_set_layout,
			                             vk::SampleCountFlagBits msaa_samples);
			~SkyboxVulkanGraphicsPipeline() = default;
		};
	}
}
