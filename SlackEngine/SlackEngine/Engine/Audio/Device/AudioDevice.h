#pragma once

#include <AL/alc.h>

namespace SlackEngine
{
	namespace Audio
	{
		class AudioDevice
		{
		private:
			ALCdevice* device_ = nullptr;
		public:
			AudioDevice();
			~AudioDevice();

			ALCdevice* get_audio_device() const;
		};
	}
}
