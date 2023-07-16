
#include "VertexBufferContainer.h"


SlackEngine::Render::VertexBufferContainer::VertexBufferContainer(vk::Buffer* input_buffer,
                                                                  const std::vector<Vertex>* input_vertices)
	: Render::BufferContainer(input_buffer), vertices_(input_vertices)
{
}

const std::vector<SlackEngine::Render::Vertex>* SlackEngine::Render::VertexBufferContainer::get_vector() const
{
	return vertices_;
}
