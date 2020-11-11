#include "WinScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"
#include "PlayScene.hpp"

void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label("YOU", "slkscr.ttf", 200, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("WIN", "slkscr.ttf", 200, halfW, halfH / 2 + 150, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("bl.png", "win/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "slkscr.ttf", 48, halfW, halfH * 3 / 2, 255, 255, 255, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("win.ogg");
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
	}
}
void WinScene::BackOnClick(int stage) {
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
