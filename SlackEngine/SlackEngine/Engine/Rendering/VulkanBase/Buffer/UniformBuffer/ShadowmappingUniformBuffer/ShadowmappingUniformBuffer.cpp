
#include "ShadowmappingUniformBuffer.h"

#include <glm/gtx/quaternion.hpp>
#include <Engine/LogicCore/Math/Transform/STransform.h>

#include "Memory/VulkanMemoryAllocator.h"

SlackEngine::Render::ShadowmappingUniformBuffer::ShadowmappingUniformBuffer(const size_t swap_chain_images_size)
{
	const vk::DeviceSize buffer_size(sizeof(OffscreenUniformBufferObject));

	uniform_buffers_.resize(swap_chain_images_size);
	uniform_buffers_memory_.resize(swap_chain_images_size);

	for (size_t i = 0; i < swap_chain_images_size; i++)
	{
		VulkanMemoryAllocator::get_instance()->create_uniform_buffer(buffer_size, uniform_buffers_[i],
		                                                             uniform_buffers_memory_[i]);
	}

	//Map memory
	mapped_memory_.resize(swap_chain_images_size);
	for (size_t i = 0; i < swap_chain_images_size; i++)
	{
		VulkanMemoryAllocator::get_instance()->map_buffer_allocation(uniform_buffers_memory_[i], &mapped_memory_[i]);
	}
}

void SlackEngine::Render::ShadowmappingUniformBuffer::update_uniform_buffer_transform(
	const Core::STransform& object_transform)
{
	//Traslate
	offscreen_ubo_.model = translate(glm::mat4(1.0f), object_transform.get_position().get_glm_vector());

	//Rotate
	const glm::mat4 rotation_matrix = toMat4(object_transform.get_quat_rotation().get_glm_quat());
	offscreen_ubo_.model = offscreen_ubo_.model * rotation_matrix;

	//Scale
	offscreen_ubo_.model = scale(offscreen_ubo_.model, object_transform.get_scale().get_glm_vector());
}

void SlackEngine::Render::ShadowmappingUniformBuffer::update_uniform_buffer_light(const float light_fov,
                                                                                  const glm::vec3& light_pos,
                                                                                  const glm::vec3& light_lookat,
                                                                                  const float z_near, const float z_far)
{
	// Matrix from light's point of view
	glm::mat4 depth_projection_matrix = glm::perspective(glm::radians(light_fov), 1.0f, z_near, z_far);
	//Invert image for openGL style
	depth_projection_matrix[1][1] *= -1;

	const glm::mat4 depth_view_matrix = glm::lookAt(light_pos, light_lookat, glm::vec3(0, 1, 0));

	offscreen_ubo_.depth_mvp = depth_projection_matrix * depth_view_matrix;
}

void SlackEngine::Render::ShadowmappingUniformBuffer::finish_update_uniform_buffer(const uint32_t current_image)
{
	std::memcpy(mapped_memory_[current_image], &offscreen_ubo_, sizeof(offscreen_ubo_));
}

glm::mat4 SlackEngine::Render::ShadowmappingUniformBuffer::get_depth_bias() const
{
	return offscreen_ubo_.depth_mvp;
}
