#pragma once

#include "CommandPool/VulkanCommandPool.h"
namespace SlackEngine
{
	namespace Render
	{
		class SingletonCommandPool : public VulkanCommandPool
		{
		private:
			//Singleton static instance
			static VulkanCommandPool* instance_;
		public:
			~SingletonCommandPool() = default;

			//Singleton static function to get or create a class instance
			static VulkanCommandPool* get_instance();
		};
	}
}
