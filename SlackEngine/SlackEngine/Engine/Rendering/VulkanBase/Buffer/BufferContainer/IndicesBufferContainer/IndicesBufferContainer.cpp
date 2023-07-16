
#include "IndicesBufferContainer.h"

#include "Buffer/BufferContainer/BufferContainer.h"

SlackEngine::Render::IndicesBufferContainer::IndicesBufferContainer(vk::Buffer* input_buffer,
                                                                    const std::vector<uint32_t>* input_indices)
	: Render::BufferContainer(input_buffer), indices_(input_indices)
{
}

const std::vector<uint32_t>* SlackEngine::Render::IndicesBufferContainer::get_vector() const
{
	return indices_;
}
