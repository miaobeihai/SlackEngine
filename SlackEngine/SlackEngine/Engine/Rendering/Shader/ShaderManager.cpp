#include "ShaderManager.h"

#include <fstream>

#include "DebugLog.h"
#include "Device/VulkanDevice.h"


//Init static instance reference

SlackEngine::Render::ShaderManager* SlackEngine::Render::ShaderManager::instance_ = nullptr;

SlackEngine::Render::ShaderManager* SlackEngine::Render::ShaderManager::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ShaderManager();
	}
	return instance_;
}

vk::ShaderModule SlackEngine::Render::ShaderManager::get_shader_module(const std::string& filename)
{
	if (loaded_shaders_.find(filename) == loaded_shaders_.end())
	{
		// Shader not found, load it
		loaded_shaders_[filename] = create_shader_module(read_file(filename));
		Debug::DebugLog::print_to_console_log("[ShaderManager] Shader '" + filename + "' loaded");
	}
	//Return the shader
	return loaded_shaders_[filename];
}

vk::ShaderModule SlackEngine::Render::ShaderManager::create_shader_module(const std::vector<char>& code)
{
	vk::ShaderModuleCreateInfo create_info(
		vk::ShaderModuleCreateFlags(),
		code.size(),
		reinterpret_cast<const uint32_t*>(code.data())
	);

	vk::ShaderModule shader_module;
	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createShaderModule(
		&create_info, nullptr, &shader_module);
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "ShaderManager: Failed to create shader module!");
	}

	return shader_module;
}

std::vector<char> SlackEngine::Render::ShaderManager::read_file(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "ShaderManager: Failed to open file '" + filename + "'!");
	}

	const size_t file_size = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(file_size);
	file.seekg(0);
	file.read(buffer.data(), file_size);
	file.close();

	return buffer;
}

SlackEngine::Render::ShaderManager::~ShaderManager()
{
	cleanup_shaders();
}

void SlackEngine::Render::ShaderManager::cleanup_shaders()
{
	vk::Device* device = VulkanDevice::get_instance()->get_logical_device();
	for (const auto& element : loaded_shaders_)
	{
		device->destroyShaderModule(element.second);
		Debug::DebugLog::print_to_console_log("[ShaderManager] Destroying Shader: '" + element.first + "'");
	}
	loaded_shaders_.clear();
}
