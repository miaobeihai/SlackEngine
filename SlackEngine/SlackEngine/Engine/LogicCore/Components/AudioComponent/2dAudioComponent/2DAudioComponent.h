#pragma once

#include <Engine/LogicCore/Components/AudioComponent/AudioComponent.h>

namespace SlackEngine
{
	namespace Core
	{
		class AudioComponent2D : public AudioComponent
		{
		public:
			AudioComponent2D(Audio::AudioSource* input_audio_source);
			~AudioComponent2D() = default;
		};
	}
}
