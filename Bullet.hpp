#ifndef BULLET_HPP
#define BULLET_HPP
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Turret.hpp"
#include "PlayerShip.hpp"
#include <random>

class PlayScene;
class PlayerShip;
class Turret;
class Bullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Turret* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(PlayerShip* playership);
public:
	PlayerShip* Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime) override;
};
#endif
