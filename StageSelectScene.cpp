#include <fstream>

#include "StageSelectScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::ifstream hscore("resources/highscore.txt");
    hscore >> highscore;
    hscore.close();
    AddNewObject(new Engine::Image("stage-select-bg.jpg", 0, 0, w, h));
    AddNewObject(new Engine::Label("HIGHSCORE : " + std::to_string(highscore), "slkscr.ttf", 48, 300, h - 50, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("butt.png", "butt-off.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Start", "slkscr.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("butt.png", "butt-off.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::SettingOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "slkscr.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("menu.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
}

void StageSelectScene::SettingOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("setting");
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StageSelectScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void StageSelectScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
