#pragma once
#include "Descriptor/DescriptorPool/BaseDescriptorPool.h"


namespace SlackEngine
{
	namespace Render
	{
		class StandardDescriptorPool : public BaseDescriptorPool
		{
		public:
			StandardDescriptorPool(size_t size);
			~StandardDescriptorPool() = default;
		};
	}
}
