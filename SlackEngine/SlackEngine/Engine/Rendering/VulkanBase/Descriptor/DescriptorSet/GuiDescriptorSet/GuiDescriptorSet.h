#pragma once
#include "Descriptor/DescriptorSet/BaseDescriptorSet.h"


namespace SlackEngine
{
	namespace Render
	{
		class GuiDescriptorSet : public BaseDescriptorSet
		{
		public:
			GuiDescriptorSet();
			~GuiDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            size_t swap_chain_images_size,
			                            vk::Sampler* texture_sampler, vk::ImageView* texture_image_view);
		};
	}
}
