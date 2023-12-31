#pragma once

#include <stb_image.h>

#include "Buffer/StagingBuffer/BaseStagingBuffer.h"

namespace SlackEngine
{
	namespace Render
	{
		class ImageStagingBuffer : public BaseStagingBuffer
		{
		public:
			ImageStagingBuffer(const vk::DeviceSize& image_size, stbi_uc* pixels);

			~ImageStagingBuffer() = default;

			static void copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
			                                 uint32_t width, uint32_t height);
			static void copy_buffer_to_image(vk::Buffer* buffer, vk::Image* image,
			                                 vk::BufferImageCopy* region, int regioncount = 1,
			                                 vk::ImageLayout layout = vk::ImageLayout::eTransferDstOptimal);
		};
	}
}
