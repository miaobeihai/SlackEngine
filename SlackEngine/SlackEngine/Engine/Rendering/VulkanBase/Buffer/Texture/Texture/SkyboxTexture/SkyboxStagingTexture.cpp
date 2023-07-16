

#include "SkyboxStagingTexture.h"

#include "DebugLog.h"
#include "Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h"

SlackEngine::Render::SkyboxStagingTexture::SkyboxStagingTexture(const std::string& file_path)
{
	stbi_uc* pixels = stbi_load(file_path.c_str(), &tex_width_, &tex_height_, &tex_channels_, STBI_rgb_alpha);

	const vk::DeviceSize image_size = tex_width_ * tex_height_ * 4;
	mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(tex_width_, tex_height_)))) + 1;

	if (!pixels)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "SkyboxStagingTexture: Failed to load texture image! (pixels not valid) - " + file_path);
	}

	staginf_buffer_ref_ = new ImageStagingBuffer(image_size, pixels);

	stbi_image_free(pixels);
}

SlackEngine::Render::SkyboxStagingTexture::~SkyboxStagingTexture()
{
	delete staginf_buffer_ref_;
}

SlackEngine::Render::BaseStagingBuffer* SlackEngine::Render::SkyboxStagingTexture::get_texture_staging_buffer() const
{
	return staginf_buffer_ref_;
}

int SlackEngine::Render::SkyboxStagingTexture::get_texture_width() const
{
	return tex_width_;
}

int SlackEngine::Render::SkyboxStagingTexture::get_texture_height() const
{
	return tex_height_;
}
