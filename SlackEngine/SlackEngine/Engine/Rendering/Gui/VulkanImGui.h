#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <glm/vec2.hpp>

#include "Buffer/GenericBuffer/GenericBuffer.h"
#include "Buffer/Texture/TextureImageView/TextureImageView.h"
#include "Buffer/Texture/TextureSampler/TextureSampler.h"
#include "Descriptor/DescriptorPool/BaseDescriptorPool.h"
#include "Descriptor/DescriptorSet/GuiDescriptorSet/GuiDescriptorSet.h"
#include "Pipeline/GuiPipeline/GuiVulkanGraphicsPipeline.h"
#include "SwapChain/VulkanSwapChain.h"

namespace SlackEngine
{
	namespace Render
	{
		// class VulkanSwapChain;
		// class GenericBuffer;
		// class BaseRenderPass;
		// class GuiVulkanGraphicsPipeline;
		// class GuiDescriptorSet;
		// class BaseDescriptorPool;
		// class TextureSampler;
		// class TextureImageView;

		class VulkanImGui
		{
		public:
			struct PushConstBlock
			{
				glm::vec2 scale;
				glm::vec2 translate;
			};

		private:
			vk::Image font_image_;
			VmaAllocation font_memory_;
			TextureImageView* front_view_ = nullptr;
			TextureSampler* sampler_ = nullptr;
			BaseDescriptorPool* descriptor_pool_ = nullptr;
			GuiDescriptorSet* descriptor_set_ = nullptr;
			GuiVulkanGraphicsPipeline* pipeline_ = nullptr;
			BaseRenderPass* gui_render_pass_ = nullptr;
			//Buffers
			//I need vectors because i need one for each command buffer (2 in total)
			GenericBuffer* vertex_buffer_;
			GenericBuffer* index_buffer_;
			int32_t vertex_count_;
			int32_t index_count_;

			PushConstBlock push_const_block_;
		public:
			explicit VulkanImGui();
			~VulkanImGui();

			void init(float width, float height);
			void init_resources(VulkanSwapChain* swap_chain);

			void update_buffers();

			void generate_empty_gui_frame() const;
			void generate_loading_gui_frame() const;
			void pre_gui_frame() const;
			void post_gui_frame() const;

			void loading_ui() const;

			GuiDescriptorSet* get_descriptor_set() const;
			GuiVulkanGraphicsPipeline* get_pipeline() const;
			GenericBuffer* get_vertex_buffer() const;
			GenericBuffer* get_index_buffer() const;
			PushConstBlock* get_push_const_block();
			BaseRenderPass* get_render_pass() const;
		};
	}
}
