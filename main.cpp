// [main.cpp]
// this template is provided for the 2D tower defense game.
// Program entry point.
// Returns program exit code.
#include "GameEngine.hpp"
#include "LOG.hpp"
#include "StageSelectScene.hpp"
#include "PlayScene.hpp"
#include "WinScene.hpp"
#include "LoseScene.hpp"
#include "StartScene.hpp"
#include "SettingScene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("setting", new SettingScene());
	game.AddNewScene("start", new StartScene());
	game.Start("start", 20, 1600, 832);
	return 0;
}
