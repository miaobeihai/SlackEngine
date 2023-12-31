#include "GuiRenderPass.h"

#include <array>

#include "DebugLog.h"
#include "Device/VulkanDevice.h"
#include "Engine/Rendering/DepthResources/VulkanDepthResources.h"


//Class

SlackEngine::Render::GuiRenderPass::GuiRenderPass(const vk::Format& swap_chain_image_format,
                                                  const vk::SampleCountFlagBits msaa_samples)
{
	const vk::AttachmentDescription color_attachment(
		vk::AttachmentDescriptionFlags(),
		swap_chain_image_format,
		msaa_samples,
		vk::AttachmentLoadOp::eLoad,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eColorAttachmentOptimal,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	const vk::AttachmentDescription depth_attachment(
		vk::AttachmentDescriptionFlags(),
		VulkanDepthResources::find_depth_format(),
		msaa_samples,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	const vk::AttachmentDescription color_attachment_resolve(
		vk::AttachmentDescriptionFlags(),
		swap_chain_image_format,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::ePresentSrcKHR
	);

	vk::AttachmentReference color_attachment_ref(
		0,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::AttachmentReference depth_attachment_ref(
		1,
		vk::ImageLayout::eDepthStencilAttachmentOptimal
	);

	vk::AttachmentReference color_attachment_resolve_ref(
		2,
		vk::ImageLayout::eColorAttachmentOptimal
	);

	vk::SubpassDescription subpass(
		vk::SubpassDescriptionFlags(),
		vk::PipelineBindPoint::eGraphics,
		0, nullptr,
		1, &color_attachment_ref,
		&color_attachment_resolve_ref,
		&depth_attachment_ref
	);

	vk::SubpassDependency dependency(
		VK_SUBPASS_EXTERNAL,
		0,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::PipelineStageFlagBits::eColorAttachmentOutput,
		vk::AccessFlags(),
		vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite
	);

	std::array<vk::AttachmentDescription, 3> attachments = {
		color_attachment, depth_attachment, color_attachment_resolve
	};

	vk::RenderPassCreateInfo render_pass_info(
		vk::RenderPassCreateFlags(),
		static_cast<uint32_t>(attachments.size()),
		attachments.data(),
		1,
		&subpass,
		1,
		&dependency
	);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createRenderPass(&render_pass_info, nullptr, &render_pass_);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "VulkanRenderPass: Failed to create render pass!");
	}
}
