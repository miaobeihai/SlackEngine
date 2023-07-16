#include <Engine/Audio/Context/AudioContext.h>
#include <stdexcept>

SlackEngine::Audio::AudioContext::AudioContext(ALCdevice* device)
{
	context_ = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context_))
	{
		throw std::runtime_error("AudioContext: Failed to make context current");
	}
}

SlackEngine::Audio::AudioContext::~AudioContext()
{
	alcDestroyContext(context_);
}
