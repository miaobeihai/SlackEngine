#pragma once
#include "Descriptor/DescriptorPool/BaseDescriptorPool.h"


namespace SlackEngine
{
	namespace Render
	{
		class GuiDescriptorPool : public BaseDescriptorPool
		{
		public:
			GuiDescriptorPool(size_t size);
		};
	}
}
