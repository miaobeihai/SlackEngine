#pragma once
#include "Pipeline/BaseVulkanGraphicsPipeline.h"
#include "RenderPass/BaseRenderPass.h"

namespace SlackEngine
{
	namespace Render
	{

		class ShadowmappingPipeline : public BaseVulkanGraphicsPipeline
		{
		public:
			ShadowmappingPipeline(const char* vertex_shader,
			                      vk::DescriptorSetLayout* descriptor_set_layout, const vk::Extent2D& shadowmapping_extent,
			                      BaseRenderPass* render_pass);
			~ShadowmappingPipeline() = default;
		};
	}
}
