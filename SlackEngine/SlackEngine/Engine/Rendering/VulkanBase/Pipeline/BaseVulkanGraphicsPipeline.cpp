
#include "BaseVulkanGraphicsPipeline.h"

#include "Device/VulkanDevice.h"

SlackEngine::Render::BaseVulkanGraphicsPipeline::~BaseVulkanGraphicsPipeline()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyPipeline(graphics_pipeline_);
	VulkanDevice::get_instance()->get_logical_device()->destroyPipelineLayout(pipeline_layout_);
}

vk::Pipeline* SlackEngine::Render::BaseVulkanGraphicsPipeline::get_graphics_pipeline()
{
	return &graphics_pipeline_;
}

vk::PipelineLayout* SlackEngine::Render::BaseVulkanGraphicsPipeline::get_pipeline_layout()
{
	return &pipeline_layout_;
}
