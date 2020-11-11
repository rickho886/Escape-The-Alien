#ifndef PLAYERSHIP_HPP
#define PLAYERSHIP_HPP
#include "Sprite.hpp"
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"
#include "PlayerAbilities.hpp"

class PlayScene;
class Turret;
class Bullet;
class PlayerAbilities;
class PlayerShip: public Engine::Sprite {
protected:
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<PlayerShip*>::iterator lockedPlayerShipIterator;
    PlayScene* getPlayScene();
    virtual void OnExplode();

public:
    int immortal;
    int pre_immortal;
	float hp = 10;
	float ticks_immortal;
	float ticks_lowhp ;
    bool Enabled = true;
    bool Preview = false;
    std::list<Turret*> lockedTurrets;
    std::list<Bullet*> lockedBullets;
    PlayerShip(std::string imgPlayerShip, float x, float y, float radius, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
    void PreAbility(int pre_ability);
    void SpecialAbility(int ability);
	void Hit(float damage);
};
#endif
