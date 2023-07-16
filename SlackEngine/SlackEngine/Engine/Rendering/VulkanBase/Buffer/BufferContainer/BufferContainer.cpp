#include "BufferContainer.h"

#include <Engine/Rendering/VulkanInclude.h>

SlackEngine::Render::BufferContainer::BufferContainer(vk::Buffer* input_buffer) : buffer_(input_buffer)
{
}

SlackEngine::Render::BufferContainer::~BufferContainer()
{
	//Empty here
}

vk::Buffer* SlackEngine::Render::BufferContainer::get_buffer() const
{
	return buffer_;
}

SlackEngine::Render::BufferContainer::operator vk::Buffer() const
{
	return *(buffer_);
}
