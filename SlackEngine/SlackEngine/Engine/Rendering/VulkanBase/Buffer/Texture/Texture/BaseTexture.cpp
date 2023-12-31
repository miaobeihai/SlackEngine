#define STB_IMAGE_IMPLEMENTATION
#include "BaseTexture.h"

#include "DebugLog.h"
#include "Buffer/BaseBuffer.h"
#include "Device/VulkanDevice.h"
#include "Engine/Rendering/DepthResources/VulkanDepthResources.h"
#include "Memory/VulkanMemoryAllocator.h"


SlackEngine::Render::BaseTexture::~BaseTexture()
{
	VulkanMemoryAllocator::get_instance()->destroy_image(texture_image_, texture_image_memory_);
}

vk::Image* SlackEngine::Render::BaseTexture::get_texture_image()
{
	return &texture_image_;
}

uint32_t SlackEngine::Render::BaseTexture::get_mip_levels() const
{
	return mip_levels_;
}

SlackEngine::Render::BaseStagingBuffer* SlackEngine::Render::BaseTexture::get_texture_staging_buffer() const
{
	return nullptr;
}

void SlackEngine::Render::BaseTexture::transition_image_layout(vk::Image* image, const vk::Format& format,
                                                               const vk::ImageLayout& old_layout,
                                                               const vk::ImageLayout& new_layout,
                                                               const uint32_t& mip_levels_data, const int layercount)
{
	const std::unique_ptr<vk::CommandBuffer> command_buffer = BaseBuffer::begin_single_time_command();

	vk::ImageMemoryBarrier barrier(
		vk::AccessFlags(),
		vk::AccessFlags(),
		old_layout,
		new_layout,
		0,
		0,
		*image
	);

	if (new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
	{
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;

		if (VulkanDepthResources::has_stencil_component(format))
		{
			barrier.subresourceRange.aspectMask |= vk::ImageAspectFlagBits::eStencil;
		}
	}
	else
	{
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
	}

	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = mip_levels_data;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = layercount;

	vk::PipelineStageFlags source_stage;
	vk::PipelineStageFlags destination_stage;

	if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eTransferDstOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eTransfer;
	}
	else if (old_layout == vk::ImageLayout::eTransferDstOptimal && new_layout == vk::ImageLayout::eShaderReadOnlyOptimal
	)
	{
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		source_stage = vk::PipelineStageFlagBits::eTransfer;
		destination_stage = vk::PipelineStageFlagBits::eFragmentShader;
	}
	else if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::
			eDepthStencilAttachmentWrite;

		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eEarlyFragmentTests;
	}
	else if (old_layout == vk::ImageLayout::eUndefined && new_layout == vk::ImageLayout::eColorAttachmentOptimal)
	{
		barrier.srcAccessMask = vk::AccessFlags();
		barrier.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;
		source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
		destination_stage = vk::PipelineStageFlagBits::eColorAttachmentOutput;
	}
	else
	{
		Debug::DebugLog::fatal_error(vk::Result(-13),
		                             "TextureImage: Unsupported layout transition! Can't continue!");
	}

	command_buffer->pipelineBarrier(
		source_stage,
		destination_stage,
		vk::DependencyFlags(),
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

	BaseBuffer::end_and_submit_single_time_command(command_buffer);
}

void SlackEngine::Render::BaseTexture::generate_mipmaps(vk::Image* image, const vk::Format& image_format,
                                                        const int32_t& tex_width, const int32_t& tex_height,
                                                        const uint32_t& mip_levels)
{
	// Check if image format supports linear blitting
	const vk::FormatProperties format_properties = VulkanDevice::get_instance()->get_physical_device()->
	                                                                             getFormatProperties(image_format);

	if (!(format_properties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eSampledImageFilterLinear))
	{
		Debug::DebugLog::fatal_error(vk::Result(-13),
		                             "TextureImage: Texture image format does not support linear blitting!");
	}

	const std::unique_ptr<vk::CommandBuffer> command_buffer = BaseBuffer::begin_single_time_command();

	vk::ImageMemoryBarrier barrier(
		vk::AccessFlags(),
		vk::AccessFlags(),
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::eUndefined,
		0,
		0,
		*image,
		vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1)
	);

	int32_t mip_width = tex_width;
	int32_t mip_height = tex_height;

	for (uint32_t i = 1; i < mip_levels; i++)
	{
		barrier.subresourceRange.baseMipLevel = i - 1;
		barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		barrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

		command_buffer->pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eTransfer,
			vk::DependencyFlags(),
			0, nullptr,
			0, nullptr,
			1, &barrier
		);

		const vk::ImageSubresourceLayers srcSubresource(
			vk::ImageAspectFlagBits::eColor,
			i - 1,
			0,
			1
		);

		const std::array<vk::Offset3D, 2> srcOffset{
			vk::Offset3D(),
			vk::Offset3D(
				mip_width,
				mip_height,
				1
			)
		};

		const vk::ImageSubresourceLayers dstSubresource(
			vk::ImageAspectFlagBits::eColor,
			i,
			0,
			1
		);

		const std::array<vk::Offset3D, 2> dstOffset{
			vk::Offset3D(),
			vk::Offset3D(
				mip_width > 1 ? mip_width / 2 : 1,
				mip_height > 1 ? mip_height / 2 : 1,
				1
			)
		};

		vk::ImageBlit blit(
			srcSubresource,
			srcOffset,
			dstSubresource,
			dstOffset
		);

		command_buffer->blitImage(
			*image,
			vk::ImageLayout::eTransferSrcOptimal,
			*image,
			vk::ImageLayout::eTransferDstOptimal,
			1,
			&blit,
			vk::Filter::eLinear
		);

		barrier.oldLayout = vk::ImageLayout::eTransferSrcOptimal;
		barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

		command_buffer->pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eFragmentShader,
			vk::DependencyFlags(),
			0,
			nullptr,
			0,
			nullptr,
			1,
			&barrier
		);

		if (mip_width > 1)
		{
			mip_width /= 2;
		}
		if (mip_height > 1)
		{
			mip_height /= 2;
		}
	}

	barrier.subresourceRange.baseMipLevel = mip_levels - 1;
	barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
	barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
	barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

	command_buffer->pipelineBarrier(
		vk::PipelineStageFlagBits::eTransfer,
		vk::PipelineStageFlagBits::eFragmentShader,
		vk::DependencyFlags(),
		0,
		nullptr,
		0,
		nullptr,
		1,
		&barrier
	);

	BaseBuffer::end_and_submit_single_time_command(command_buffer);
}
