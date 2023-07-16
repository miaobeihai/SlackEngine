


#include "BaseRenderPass.h"

#include "Device/VulkanDevice.h"

SlackEngine::Render::BaseRenderPass::~BaseRenderPass()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyRenderPass(render_pass_);
}

vk::RenderPass* SlackEngine::Render::BaseRenderPass::get_render_pass()
{
	return &render_pass_;
}

SlackEngine::Render::BaseRenderPass::operator vk::RenderPass() const
{
	return render_pass_;
}
