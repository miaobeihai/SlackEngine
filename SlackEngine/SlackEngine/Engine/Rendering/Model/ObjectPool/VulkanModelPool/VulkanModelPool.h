#pragma once

#include <memory>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <unordered_map>

namespace SlackEngine
{
	namespace Render
	{
		class VulkanModelPool
		{
		private:
			//Singleton static instance
			static VulkanModelPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanModelPool() = default;

			//I associate the model path with the with the corresponding VulkanModel
			//So i create only one VulkanModel for every model loaded
			std::unordered_map<std::string, std::shared_ptr<VulkanModel>> model_pool_;
		public:
			//Singleton static function to get or create a class instance
			static VulkanModelPool* get_instance();

			std::shared_ptr<VulkanModel> get_model(const std::string& model_path);

			~VulkanModelPool();

			void clear_memory();
		};
	}
}
