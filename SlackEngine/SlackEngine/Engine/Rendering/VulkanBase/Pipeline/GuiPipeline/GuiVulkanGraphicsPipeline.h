#pragma once
#include "Pipeline/BaseVulkanGraphicsPipeline.h"
#include "RenderPass/BaseRenderPass.h"

namespace SlackEngine
{
	namespace Render
	{

		class GuiVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			GuiVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                          vk::DescriptorSetLayout* descriptor_set_layout, size_t block_size,
			                          BaseRenderPass* render_pass);
			~GuiVulkanGraphicsPipeline() = default;
		};
	}
}
