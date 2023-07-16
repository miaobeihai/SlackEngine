#include <Engine/Rendering/Model/ObjectPool/VulkanModelPool/VulkanModelPool.h>
#include <memory>
#include <Engine/Debug/DebugLog.h>

//Init static instance reference

SlackEngine::Render::VulkanModelPool* SlackEngine::Render::VulkanModelPool::instance_ = nullptr;

SlackEngine::Render::VulkanModelPool* SlackEngine::Render::VulkanModelPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanModelPool();
	}
	return instance_;
}

std::shared_ptr<SlackEngine::Render::VulkanModel> SlackEngine::Render::VulkanModelPool::get_model(
	const std::string& model_path)
{
	if (model_pool_.find(model_path) == model_pool_.end())
	{
		// Model not found, create it
		model_pool_[model_path] = std::make_shared<VulkanModel>(model_path);
		Debug::DebugLog::print_to_console_log("[VulkanModelPool] Model loaded and created");
	}
	return model_pool_[model_path];
}

SlackEngine::Render::VulkanModelPool::~VulkanModelPool()
{
	clear_memory();
}

void SlackEngine::Render::VulkanModelPool::clear_memory()
{
	std::vector<std::string> model_to_erase;
	for (const auto& model : model_pool_)
	{
		if (model.second.use_count() == 1)
		{
			model_to_erase.push_back(model.first);
		}
	}
	for (const auto& model_key : model_to_erase)
	{
		Debug::DebugLog::print_to_console_log("[VulkanModelPool] Removing 3D model '"
			+ model_key + "' from pool memory");
		model_pool_[model_key] = nullptr;
		model_pool_.erase(model_key);
	}
}
