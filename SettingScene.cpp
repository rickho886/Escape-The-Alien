#include "SettingScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"

void SettingScene::Initialize() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("settings-bg.jpg", 0, 0, w, h));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("snip.JPG", "snipp.JPG", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&SettingScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "slkscr.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
	Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190*AudioHelper::BGMVolume, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&SettingScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "slkscr.ttf", 40, 40 + halfW - 60 - 95, halfH - 50, 0, 0, 0, 255, 0.5, 0.5));
    sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190*AudioHelper::SFXVolume, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&SettingScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "slkscr.ttf", 40, 40 + halfW - 60 - 95, halfH + 50, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("setting.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}

void SettingScene::BackOnClick(int stage) {
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void SettingScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void SettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
