

#include "BaseFrameBuffer.h"

#include "Device/VulkanDevice.h"

SlackEngine::Render::BaseFrameBuffer::~BaseFrameBuffer()
{
	for (auto& framebuffer : framebuffers_)
	{
		VulkanDevice::get_instance()->get_logical_device()->destroyFramebuffer(framebuffer);
	}
}

const std::vector<vk::Framebuffer>* SlackEngine::Render::BaseFrameBuffer::get_framebuffers_vector() const
{
	return &framebuffers_;
}

size_t SlackEngine::Render::BaseFrameBuffer::get_framebuffers_vector_size() const
{
	return framebuffers_.size();
}
