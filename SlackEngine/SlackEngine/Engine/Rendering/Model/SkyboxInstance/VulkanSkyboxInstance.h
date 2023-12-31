#pragma once

#include <memory>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

#include "Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h"
#include "Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h"
#include "Buffer/UniformBuffer/SkyboxUniformBuffer/SkyboxUniformBuffer.h"
#include "Engine/Rendering/Model/Material/SkyboxMaterial/SkyboxMaterial.h"

namespace SlackEngine
{
	namespace Render
	{
		// class Camera;
		// class VulkanSwapChain;
		// class IndicesBufferContainer;
		// class VertexBufferContainer;
		// class SkyboxMaterial;
		// class SkyboxUniformBuffer;
		// class BasicMaterial;

		class VulkanSkyboxInstance
		{
		private:
			std::shared_ptr<VulkanModel> vulkan_render_model_ = nullptr;
			SkyboxUniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			SkyboxMaterial* skybox_material_ = nullptr;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> mesh_buffers_;

			Core::STransform skybox_transform_;
			bool skybox_transform_updated_ = false;
		public:
			VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     const std::string& model_path, const std::array<std::string, 6>& texture_path,
			                     VulkanSwapChain* swap_chain);
			~VulkanSkyboxInstance();

			void update_uniform_buffer(uint32_t current_image, Camera* render_camera);

			int get_cubemap_size() const;
			void set_cubemap_size(unsigned int new_size);

			SkyboxUniformBuffer* get_vulkan_render_uniform_buffer() const;
			BasicMaterial* get_skybox_material() const;
			const std::pair<VertexBufferContainer*, IndicesBufferContainer*>* get_mesh_buffers() const;
		};
	}
}
