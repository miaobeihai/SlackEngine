

#include "VulkanSkyboxInstance.h"

#include "DebugLog.h"
#include "Buffer/UniformBuffer/SkyboxUniformBuffer/SkyboxUniformBuffer.h"
#include "Engine/Rendering/Model/Material/SkyboxMaterial/SkyboxMaterial.h"
#include "Engine/Rendering/Model/ObjectPool/VulkanModelBuffersPool/VulkanModelBuffersPool.h"
#include "Engine/Rendering/Model/ObjectPool/VulkanModelPool/VulkanModelPool.h"
#include "SwapChain/VulkanSwapChain.h"

SlackEngine::Render::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string& vertex_shader_path,
                                                                const std::string& fragment_shader_path,
                                                                const std::string& model_path,
                                                                const std::array<std::string, 6>& texture_path,
                                                                VulkanSwapChain* swap_chain)
{
	//CREATE UNIFORM BUFFER
	vulkan_render_uniform_buffer_ = new SkyboxUniformBuffer(swap_chain->get_swap_chain_images_vector()->size());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	//CREATE MATERIAL(S)
	skybox_material_ = new SkyboxMaterial();
	skybox_material_->create_pipeline(vertex_shader_path,
	                                  fragment_shader_path, swap_chain);
	skybox_material_->create_skybox_texture(texture_path);
	skybox_material_->create_descriptor_sets(swap_chain, vulkan_render_uniform_buffer_);
	//LOADING 3D MODEL AND BUFFERS
	vulkan_render_model_ = VulkanModelPool::get_instance()->get_model(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	if (vulkan_render_model_->get_meshes()->size() > 1)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13),
		                             "Cannot use a cubemap with a model containing more than one mesh!");
	}
	mesh_buffers_ = VulkanModelBuffersPool::get_instance()->get_model_buffers(model_path, vulkan_render_model_);
	skybox_transform_.set_position(Core::SVector3());
	skybox_transform_updated_ = true;
	skybox_transform_.set_scale(Core::SVector3(50, 50, 50));
}

SlackEngine::Render::VulkanSkyboxInstance::~VulkanSkyboxInstance()
{
	delete skybox_material_;
	delete vulkan_render_uniform_buffer_;
}

void SlackEngine::Render::VulkanSkyboxInstance::update_uniform_buffer(uint32_t current_image,
                                                                      Camera* render_camera)
{
	//Update transform when necessary
	if (skybox_transform_updated_)
	{
		vulkan_render_uniform_buffer_->update_uniform_buffer_transform(skybox_transform_);
		skybox_transform_updated_ = false;
	}

	//Update camera info
	vulkan_render_uniform_buffer_->update_uniform_buffer_camera_data(render_camera);

	//Update the uniform buffer
	vulkan_render_uniform_buffer_->finish_update_uniform_buffer(current_image);
}

int SlackEngine::Render::VulkanSkyboxInstance::get_cubemap_size() const
{
	return static_cast<int>(skybox_transform_.get_scale().get_x());
}

void SlackEngine::Render::VulkanSkyboxInstance::set_cubemap_size(const unsigned int new_size)
{
	const float size = static_cast<float>(new_size);
	skybox_transform_.set_scale(Core::SVector3(size, size, size));
	skybox_transform_updated_ = true;
}

SlackEngine::Render::SkyboxUniformBuffer* SlackEngine::Render::VulkanSkyboxInstance::
get_vulkan_render_uniform_buffer() const
{
	return vulkan_render_uniform_buffer_;
}

SlackEngine::Render::BasicMaterial* SlackEngine::Render::VulkanSkyboxInstance::get_skybox_material() const
{
	return skybox_material_;
}

const std::pair<SlackEngine::Render::VertexBufferContainer*, SlackEngine::Render::IndicesBufferContainer*>* SlackEngine
::
Render::VulkanSkyboxInstance::get_mesh_buffers() const
{
	return &mesh_buffers_->at(0);
}
