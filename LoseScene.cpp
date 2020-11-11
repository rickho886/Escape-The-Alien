#include "LoseScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"

void LoseScene::Initialize() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label("GAME", "slkscr.ttf", 200, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("OVER", "slkscr.ttf", 200, halfW, halfH / 2 + 150, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("bl.png", "win/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "slkscr.ttf", 48, halfW, halfH * 3 / 2, 255, 255, 255, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("lose.ogg");
}
void LoseScene::BackOnClick(int stage) {
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
