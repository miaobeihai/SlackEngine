#pragma once
#include "Vertex.h"
#include "Buffer/StagingBuffer/BaseStagingBuffer.h"


namespace SlackEngine
{
	namespace Render
	{
		class VertexStagingBuffer : public BaseStagingBuffer
		{
		public:
			VertexStagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<Vertex>* vector_data);

			~VertexStagingBuffer() = default;
		};
	}
}
