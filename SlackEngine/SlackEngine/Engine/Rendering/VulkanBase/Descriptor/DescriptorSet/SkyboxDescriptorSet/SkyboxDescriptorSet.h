#pragma once
#include "Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h"
#include "Descriptor/DescriptorSet/BaseDescriptorSet.h"


namespace SlackEngine
{
	namespace Render
	{
		class SkyboxDescriptorSet : public BaseDescriptorSet
		{
		public:
			SkyboxDescriptorSet();
			~SkyboxDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            size_t swap_chain_images_size,
			                            const std::vector<vk::Buffer>* uniform_buffers,
			                            vk::ImageView* texture_image_view, vk::Sampler* texture_sampler,
			                            const vk::DeviceSize& buffer_info_size = sizeof(UniformBufferObject));
		};
	}
}
