#include <Engine/LogicCore/Components/AudioComponent/AudioComponent.h>
#include <Engine/Audio/Source/AudioSource.h>

SlackEngine::Core::AudioComponent::AudioComponent(Audio::AudioSource* input_audio_source)
	: SComponent("AudioComponent"), audio_source_(input_audio_source)
{
}

SlackEngine::Core::AudioComponent::~AudioComponent()
{
	delete audio_source_;
}

void SlackEngine::Core::AudioComponent::set_source_pitch(const float pitch) const
{
	audio_source_->set_source_pitch(pitch);
}

void SlackEngine::Core::AudioComponent::set_source_gain(const float gain) const
{
	audio_source_->set_source_gain(gain);
}

void SlackEngine::Core::AudioComponent::set_source_loop(const bool loop) const
{
	audio_source_->set_source_loop(loop);
}

bool SlackEngine::Core::AudioComponent::is_playing() const
{
	return audio_source_->is_playing();
}

void SlackEngine::Core::AudioComponent::play() const
{
	audio_source_->play();
}

void SlackEngine::Core::AudioComponent::stop() const
{
	audio_source_->stop();
}

void SlackEngine::Core::AudioComponent::pause() const
{
	audio_source_->pause();
}

void SlackEngine::Core::AudioComponent::rewind() const
{
	audio_source_->rewind();
}

SlackEngine::Audio::AudioSource* SlackEngine::Core::AudioComponent::get_raw_source() const
{
	return audio_source_;
}
