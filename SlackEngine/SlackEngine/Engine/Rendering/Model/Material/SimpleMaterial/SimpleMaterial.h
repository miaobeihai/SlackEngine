#pragma once
#include "Buffer/Texture/Texture/BaseTexture.h"
#include "Buffer/Texture/TextureImageView/TextureImageView.h"
#include "Buffer/Texture/TextureSampler/TextureSampler.h"
#include "Engine/Rendering/Model/Material/BasicMaterial.h"


namespace SlackEngine
{
	namespace Render
	{
		class StandardUniformBuffer;
		class VulkanSwapChain;
		class BaseDescriptorPool;

		class SimpleMaterial : public BasicMaterial
		{
		private:
			std::shared_ptr<BaseTexture> vulkan_texture_image_ = nullptr;
			std::shared_ptr<TextureImageView> vulkan_texture_image_view_ = nullptr;
			std::shared_ptr<TextureSampler> vulkan_texture_sampler_ = nullptr;
			BaseDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
		public:
			SimpleMaterial();
			~SimpleMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     VulkanSwapChain* swap_chain);

			void create_texture(const std::string& texture_path);

			void create_descriptor_sets(VulkanSwapChain* swap_chain,
			                            StandardUniformBuffer* uniform_buffer);
		};
	}
}
