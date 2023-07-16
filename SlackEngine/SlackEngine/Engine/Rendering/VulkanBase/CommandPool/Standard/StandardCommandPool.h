#pragma once
#include "CommandPool/VulkanCommandPool.h"

namespace SlackEngine
{
	namespace Render
	{
		class StandardCommandPool : public VulkanCommandPool
		{
		public:
			StandardCommandPool() = default;
			~StandardCommandPool() = default;
		};
	}
}
