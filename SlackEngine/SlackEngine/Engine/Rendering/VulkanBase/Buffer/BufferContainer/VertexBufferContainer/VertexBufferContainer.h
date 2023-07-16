#pragma once
#include <vector>

#include "Vertex.h"
#include "Buffer/BufferContainer/BufferContainer.h"


namespace SlackEngine
{
	namespace Render
	{
		class VertexBufferContainer : public BufferContainer
		{
		private:
			const std::vector<Vertex>* vertices_;
		public:
			VertexBufferContainer(vk::Buffer* input_buffer, const std::vector<Vertex>* input_vertices);
			~VertexBufferContainer() = default;

			const std::vector<Vertex>* get_vector() const;
		};
	}
}
