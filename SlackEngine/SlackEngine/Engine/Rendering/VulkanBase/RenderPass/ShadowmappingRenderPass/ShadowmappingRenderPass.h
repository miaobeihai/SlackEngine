#pragma once
#include "RenderPass/BaseRenderPass.h"


namespace SlackEngine
{
	namespace Render
	{
		class ShadowmappingRenderPass : public BaseRenderPass
		{
		public:
			ShadowmappingRenderPass(const vk::Format& depth_format);

			~ShadowmappingRenderPass() = default;
		};
	}
}
