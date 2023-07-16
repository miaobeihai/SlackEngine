#pragma once

#include <Buffer/StagingBuffer/BaseStagingBuffer.h>

namespace SlackEngines
{
	namespace Render
	{
		class IndicesStagingBuffer : public SlackEngine::Render::BaseStagingBuffer
		{
		public:
			IndicesStagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<uint32_t>* vector_data);

			~IndicesStagingBuffer() = default;
		};
	}
}
