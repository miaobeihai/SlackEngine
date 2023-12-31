#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>
#include "CommandPool/VulkanCommandPool.h"

namespace SlackEngine
{
	namespace Render
	{
		class VulkanCommandPool;

		class BaseCommandBuffer
		{
		protected:
			std::vector<vk::CommandBuffer> command_buffers_;
			vk::RenderPassBeginInfo render_pass_info_;
			VulkanCommandPool* command_pool_ref_ = nullptr;
		public:
			BaseCommandBuffer() = default;

			virtual ~BaseCommandBuffer() = 0;

			void begin_command_buffer(vk::CommandBufferUsageFlagBits flag);

			void close_command_buffer();

			void end_command_buffer_render_pass();

			void reset_command_buffer();

			void free_command_buffers();

			const std::vector<vk::CommandBuffer>* get_command_buffers_vector() const;
		};
	}
}
