#include "StartScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"
#include "PlayScene.hpp"

void StartScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("main-bg.jpg", 0, 0, w, h));
	AddNewObject(new Engine::Label("Escape The Aliens", "slkscr.ttf", 100, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/out.png", "win/in.png", halfW - 350, halfH * 4 / 2.9 - 50, 700, 160);
	btn->SetOnClickCallback(std::bind(&StartScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Press to Continue", "slkscr.ttf", 48, halfW, halfH * 3 / 2 - 5, 0, 0, 0, 255, 0.5, 0.5));
	bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("start.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
}
void StartScene::BackOnClick(int stage) {
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
