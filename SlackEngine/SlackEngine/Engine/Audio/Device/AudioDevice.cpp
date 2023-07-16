#include <Engine/Audio/Device/AudioDevice.h>
#include <stdexcept>

SlackEngine::Audio::AudioDevice::AudioDevice()
{
	device_ = alcOpenDevice(nullptr);
	if (!device_)
	{
		throw std::runtime_error("AudioDevice: Failed to open default device");
	}
}

SlackEngine::Audio::AudioDevice::~AudioDevice()
{
	alcCloseDevice(device_);
}

ALCdevice* SlackEngine::Audio::AudioDevice::get_audio_device() const
{
	return device_;
}
