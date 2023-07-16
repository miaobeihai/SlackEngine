#include <Engine/Rendering/Model/Material/BasicMaterial.h>

#include "Descriptor/DescriptorSet/BaseDescriptorSet.h"

SlackEngine::Render::BasicMaterial::~BasicMaterial()
{
	delete_graphics_pipeline();
	delete vulkan_render_descriptor_set_;
}

void SlackEngine::Render::BasicMaterial::delete_graphics_pipeline()
{
	vulkan_render_graphics_pipeline_ = nullptr;
}

std::shared_ptr<SlackEngine::Render::BaseVulkanGraphicsPipeline> SlackEngine::Render::BasicMaterial::
get_vulkan_render_graphics_pipeline() const
{
	return vulkan_render_graphics_pipeline_;
}

SlackEngine::Render::BaseDescriptorSet* SlackEngine::Render::BasicMaterial::get_vulkan_render_descriptor_set() const
{
	return vulkan_render_descriptor_set_;
}
