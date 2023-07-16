#pragma once
#include "Buffer/CommandBuffer/BaseCommandBuffer.h"
#include "Buffer/FrameBuffer/BaseFrameBuffer.h"
#include "Engine/Rendering/Camera/Camera.h"
#include "Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h"
#include "Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h"
#include "Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h"


namespace SlackEngine
{
	namespace Render
	{
		// class VulkanSkyboxInstance;
		// class BaseFrameBuffer;
		// class VulkanMeshInstance;
		// class StandardShadowmapping;
		// class Camera;

		class StandardCommandBuffer : public BaseCommandBuffer
		{
		private:
			Camera* current_camera_ = nullptr;

			void pre_shadow_mesh_commands(StandardShadowmapping* shadowmapping);
		public:
			explicit StandardCommandBuffer(VulkanCommandPool* command_pool, int16_t cb_size);

			~StandardCommandBuffer() = default;

			void init_shadow_map(StandardShadowmapping* shadowmapping);
			void load_mesh_shadow_map(StandardShadowmapping* shadowmapping,
			                          VulkanMeshInstance* mesh);

			void init_command_buffer(const vk::Extent2D& input_swap_chain_extent_ref,
			                         BaseFrameBuffer* swap_chain_frame_buffer);
			void init_current_camera(Camera* current_camera);

			void load_skybox(VulkanSkyboxInstance* skybox_ref);
			void load_mesh(VulkanMeshInstance* mesh);
		};
	}
}
