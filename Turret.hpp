#ifndef TURRET_HPP
#define TURRET_HPP
#include "Sprite.hpp"
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "PlayerShip.hpp"

class PlayScene;
class Bullet;
class PlayerShip;
class Turret: public Engine::Sprite {
protected:
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    virtual void CreateBullet() = 0;
    virtual void OnExplode();
    float start = 1;
    int dir;
public:
    bool Enabled = true;
    bool Preview = false;
    PlayerShip* Target = nullptr;
    std::list<Turret*> lockedTurrets;
    std::list<Bullet*> lockedBullets;
    Turret(std::string imgTurret, float x, float y, float radius, float coolDownp);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif
