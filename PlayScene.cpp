#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <queue>
#include <string>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "Enemy2.hpp"
#include "Enemy1.hpp"
#include "PlayScene.hpp"
#include "PlayerShip.hpp"
#include "Sprite.hpp"
#include "BonusObjects.hpp"

bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
	mapState.clear();
	keyStrokes.clear();
	immortal_count = 0;
	ticks_tower = 0;
	ticks_tower2 = 0;
	ticks_tower3 = 0;
	ticks_lose = 0;
	ticks_bonus = 0;
	player_hp = 10;
	life = 0;
	start = 1;
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(BGGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	AddNewObject(PlayerShipGroup = new Group());
	AddNewObject(PlayerAbilitiesGroup = new Group());
	AddNewControlObject(UIGroup = new Group());
	ReadMap();
	mapDistance = CalculateBFSDistance();
	ConstructUI();
	preview = nullptr;
	if(MapId == 1) {
        playBG = new Engine::Image("play-bg1.jpg", 0, 0, Engine::GameEngine::GetInstance().GetScreenSize().x, Engine::GameEngine::GetInstance().GetScreenSize().y);
        score = 0;
	}
	if(MapId == 2) playBG = new Engine::Image("play-bg2.jpg", 0, 0, Engine::GameEngine::GetInstance().GetScreenSize().x, Engine::GameEngine::GetInstance().GetScreenSize().y);
	if(MapId == 3) playBG = new Engine::Image("play-bg3.jpg", 0, 0, Engine::GameEngine::GetInstance().GetScreenSize().x, Engine::GameEngine::GetInstance().GetScreenSize().y);
	BGGroup->AddNewObject(playBG);
	AudioHelper::PlayBGM("play-bgm.ogg");
	player = new PlayerShip("play/plane.png", 800, 500, 25, 0);
	player->Visible = true;
	PlayerShipGroup->AddNewObject(player);
	time = MapId * 15;
}
void PlayScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    player_hp = player->hp;
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
		preview->Update(deltaTime);
	}
	ticks += deltaTime;
	ticks_tower += deltaTime;
	ticks_tower2 += deltaTime;
	ticks_bonus += deltaTime;
	if(ticks > 1) {
        TimeCounter(0);
        ticks = 0;
	}

	if(ticks_tower > 4 || start == 1) {
        start = 0;
        ticks_tower = 0;
        int x = 0, y = 0;
        while(1) {
            if(x > 30 && (x < Engine::GameEngine::GetInstance().GetScreenSize().x - 30) && y > 30 && (y < Engine::GameEngine::GetInstance().GetScreenSize().y - 30)) break;
            x = rand();
            y = rand();
        }
        UIBtnClicked(0);
        OnMouseUp(1, x, y);
        OnMouseDown(1, x, y);
	}

	if(ticks_tower2 > 12 && (MapId > 1)) {
        ticks_tower2 = 0;
        int x = 0, y = 0;
        while(1) {
            if(x > 30 && (x < Engine::GameEngine::GetInstance().GetScreenSize().x - 30) && y > 30 && (y < Engine::GameEngine::GetInstance().GetScreenSize().y - 30)) break;
            x = rand();
            y = rand();
        }
        UIBtnClicked(1);
        OnMouseUp(1, x, y);
        OnMouseDown(1, x, y);
	}

	if(ticks_bonus > 10) {
        ticks_bonus = 0;
        int x = 0, y = 0;
        while(1) {
            if(x > 30 && (x < Engine::GameEngine::GetInstance().GetScreenSize().x - 30) && y > 30 && (y < Engine::GameEngine::GetInstance().GetScreenSize().y - 30)) break;
            x = rand();
            y = rand();
        }
        PlayerAbilitiesGroup->AddNewObject(new BonusObjects(Engine::Point(x, y)));
	}

	if(PlayerShipGroup->GetObjects().empty()) {
        ticks_lose += deltaTime;
        if(ticks_lose > 0.6) {
            writeScore();
            Engine::GameEngine::GetInstance().ChangeScene("lose");
        }
	}
}

void PlayScene::Draw() const {
	IScene::Draw();
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
	IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
	IScene::OnMouseUp(button, mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
			if (!preview)
				return;
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			EnemyGroup->AddNewObject(preview);
			preview->Update(0);
			preview = nullptr;
			OnMouseMove(mx, my);
	}
}
void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
    if(keyCode == ALLEGRO_KEY_F5 && player->hp > 0) {
        AudioHelper::PlayAudio("click.ogg");
        player->hp = 10;
        LifeUpdate(player->hp);
	}
	if(keyCode == ALLEGRO_KEY_I) {
        if(player->pre_immortal == 1) {
            player->SpecialAbility(0);
            ImmortalCount(0);
        }
	} /*else {
        keyStrokes.push_back(keyCode);
		if (keyStrokes.size() > code.size())
			keyStrokes.pop_front();
		if (keyCode == ALLEGRO_KEY_F5 && keyStrokes.size() == code.size()) {
			auto it = keyStrokes.begin();
			for (int c : code) {
				if (*it != c && (c == ALLEGRO_KEYMOD_SHIFT && *it != ALLEGRO_KEY_F6))
					return;
				++it;
			}
			player->hp = 10;
		}
	}*/
}
void PlayScene::TimeCounter(int score_manipulate) {
	if(!score_manipulate) {
	    time--;
        score += MapId;
	} else if(!player->immortal){
        score += score_manipulate;
    }
	UITime->Text = std::string("Time ") + std::to_string(time);
	UIScore->Text = std::string("Score ") + std::to_string(score);
	if (time <= 0) {
        if(MapId == 1) {
            PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
            scene->MapId = 2;
            Engine::GameEngine::GetInstance().ChangeScene("play");
        } else if(MapId == 2) {
            PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
            scene->MapId = 3;
            Engine::GameEngine::GetInstance().ChangeScene("play");
        } else if(MapId == 3) {
            writeScore();
            Engine::GameEngine::GetInstance().ChangeScene("win");
        }
	}
}


void PlayScene::LifeUpdate(int life) {
	this->player_hp = life;
	UILife->Text = std::string("Life ") + std::to_string(player_hp);
}

void PlayScene::ImmortalCount(int count) {
    this->immortal_count = count;
    UI_IC->Text = std::string("Immortal ") + std::to_string(immortal_count);
}

int PlayScene::getScore() {
    return score;
}

void PlayScene::writeScore() {
    std::ifstream read_hscore("resources/highscore.txt");
    read_hscore >> read_score;
    std::ofstream hscore("resources/highscore.txt");
    printf("%d\n", read_score);
    printf("%d\n", score);
    if(read_score < score) hscore << score;
    else hscore << read_score;
    read_hscore.close();
    hscore.close();
}

void PlayScene::ReadMap() {
	std::string filename = std::string("resources/map") + std::to_string(MapId) + ".txt";
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			if (num)
				TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			else
				TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
		}
	}
}

void PlayScene::ConstructUI() {
	UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "slkscr.ttf", 30, 70, 700, 255, 255, 255));
	UIGroup->AddNewObject(UITime = new Engine::Label(std::string("Time ") + std::to_string(time), "slkscr.ttf", 48, 70, 750, 255, 255, 255));
	UIGroup->AddNewObject(UILife = new Engine::Label(std::string("Life ") + std::to_string(player_hp), "slkscr.ttf", 30, 70, 650, 255, 255, 255));
	UIGroup->AddNewObject(UI_IC = new Engine::Label(std::string("Immortal ") + std::to_string(immortal_count), "slkscr.ttf", 30, 70, 600, 255, 255, 255));
	UIGroup->AddNewObject(UIScore = new Engine::Label(std::string("Score ") + std::to_string(score), "slkscr.ttf", 30, 70, 550, 255, 255, 255));
}

void PlayScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
	if (id == 0)
		preview = new Enemy1(0, 0);
	else if (id == 1)
		preview = new Enemy2(0, 0);
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Enabled = false;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
	std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
	std::queue<Engine::Point> que;
	if (mapState[MapHeight - 1][MapWidth - 1] != TILE_DIRT)
		return map;
	que.push(Engine::Point(MapWidth - 1, MapHeight - 1));
	map[MapHeight - 1][MapWidth - 1] = 0;
	while (!que.empty()) {
		Engine::Point p = que.front();
		que.pop();
		if(p.y >= 0 && p.y <= MapHeight - 1 && p.x - 1 >= 0 && p.x - 1 <= MapWidth - 1) {
            if(map[p.y][p.x - 1] == - 1 && mapState[p.y][p.x - 1] == TILE_DIRT) {
                que.push(Engine::Point(p.x - 1, p.y));
                map[p.y][p.x - 1] = map[p.y][p.x] + 1;
            }
		}
		if(p.y >= 0 && p.y <= MapHeight - 1 && p.x + 1 >= 0 && p.x + 1 <= MapWidth - 1) {
            if(map[p.y][p.x + 1] == - 1 && mapState[p.y][p.x + 1] == TILE_DIRT) {
                que.push(Engine::Point(p.x + 1, p.y));
                map[p.y][p.x + 1] = map[p.y][p.x] + 1;
            }
		}
		if(p.y - 1>= 0 && p.y - 1<= MapHeight - 1 && p.x >= 0 && p.x <= MapWidth - 1) {
            if(map[p.y - 1][p.x] == - 1 && mapState[p.y - 1][p.x] == TILE_DIRT) {
                que.push(Engine::Point(p.x, p.y - 1));
                map[p.y - 1][p.x] = map[p.y][p.x] + 1;
            }
		}
		if(p.y + 1>= 0 && p.y + 1<= MapHeight - 1 && p.x >= 0 && p.x <= MapWidth - 1) {
            if(map[p.y + 1][p.x] == - 1 && mapState[p.y + 1][p.x] == TILE_DIRT) {
                que.push(Engine::Point(p.x, p.y + 1));
                map[p.y + 1][p.x] = map[p.y][p.x] + 1;
            }
		}
	}
	return map;
}
