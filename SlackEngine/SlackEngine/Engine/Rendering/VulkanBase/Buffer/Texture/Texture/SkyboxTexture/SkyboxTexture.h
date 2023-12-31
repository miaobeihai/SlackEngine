#pragma once

#include <string>
#include <vector>

#include "Buffer/Texture/Texture/BaseTexture.h"

namespace SlackEngine
{
	namespace Render
	{
		class SkyboxTexture : public BaseTexture
		{
		private:
			std::vector<BaseTexture*> images_;

			int cube_image_size_;
		public:
			SkyboxTexture(const std::array<std::string, 6>& files_path);
			~SkyboxTexture();

			void delete_temporary_images();

			int get_texture_width() const override;
			int get_texture_height() const override;
		};
	}
}
