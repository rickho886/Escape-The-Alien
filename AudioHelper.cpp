#include "LOG.hpp"
#include "AudioHelper.hpp"
#include "Resources.hpp"

float AudioHelper::BGMVolume = 1.0;
float AudioHelper::SFXVolume = 1.0;
ALLEGRO_SAMPLE_ID AudioHelper::PlayAudio(const std::string& audio) {
	ALLEGRO_SAMPLE* sample = Engine::Resources::GetInstance().GetSample(audio).get();
	ALLEGRO_SAMPLE_ID id;
	if (!al_play_sample(sample, SFXVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &id))
		Engine::LOG(Engine::INFO) << "failed to play audio (once)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (once)";
	return id;
}
ALLEGRO_SAMPLE_ID AudioHelper::PlayBGM(const std::string& audio) {
	ALLEGRO_SAMPLE* sample = Engine::Resources::GetInstance().GetSample(audio).get();
	ALLEGRO_SAMPLE_ID id;
	if (!al_play_sample(sample, BGMVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &id))
		Engine::LOG(Engine::INFO) << "failed to play audio (bgm)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (bgm)";
	return id;
}
void AudioHelper::StopBGM(ALLEGRO_SAMPLE_ID sample) {
	al_stop_sample(&sample);
	Engine::LOG(Engine::INFO) << "stopped audio (bgm)";
}
