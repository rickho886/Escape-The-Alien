#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <vector>
#include "IScene.hpp"
#include "Sprite.hpp"
#include "Label.hpp"
#include "Turret.hpp"
#include "PlayerShip.hpp"

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
protected:
	int time;
	int life;
public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	int start;
	int player_hp;
	int immortal_count;
	int score;
	int read_score;
	float ticks;
	float ticks_tower;
	float ticks_tower2;
	float ticks_tower3;
	float ticks_lose;
	float ticks_bonus;
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* BGGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* PlayerShipGroup;
	Group* PlayerAbilitiesGroup;
	Group* UIGroup;
	Engine::Label* UILife;
	Engine::Label* UITime;
	Engine::Label* UI_IC;
	Engine::Label* UIScore;
	Engine::Image* playBG;
	PlayerShip* player;
	Turret* preview;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void TimeCounter(int score_manipulate);
	void LifeUpdate(int life);
	void ImmortalCount(int count);
	void BonusScore();
	void writeScore();
	void ReadMap();
	void ConstructUI();
	void UIBtnClicked(int id);
	int getScore();
	std::vector<std::vector<int>> CalculateBFSDistance();
};
#endif
