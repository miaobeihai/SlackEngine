#include <Engine/Audio/Buffer/AudioBuffer.h>

bool SlackEngine::Audio::AudioBuffer::is_stereo(const short channels)
{
	return channels > 1;
}

ALenum SlackEngine::Audio::AudioBuffer::to_al_format(const short channels, const short samples)
{
	const bool stereo = is_stereo(channels);

	switch (samples)
	{
	case 16:
		{
			if (stereo)
			{
				return AL_FORMAT_STEREO16;
			}
			return AL_FORMAT_MONO16;
		}
	default:
		return -1;
	}
}

SlackEngine::Audio::AudioBuffer::AudioBuffer()
{
	alGenBuffers(static_cast<ALuint>(1), &buffer_);
}

SlackEngine::Audio::AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &buffer_);
}

ALuint* SlackEngine::Audio::AudioBuffer::get_buffer()
{
	return &buffer_;
}

bool SlackEngine::Audio::AudioBuffer::get_is_stereo() const
{
	return is_stereo_;
}
