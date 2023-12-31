#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace SlackEngine
{
	namespace Render
	{
		class BaseFrameBuffer
		{
		protected:
			std::vector<vk::Framebuffer> framebuffers_;
		public:
			BaseFrameBuffer() = default;
			virtual ~BaseFrameBuffer() = 0;

			const std::vector<vk::Framebuffer>* get_framebuffers_vector() const;
			size_t get_framebuffers_vector_size() const;
		};
	}
}
