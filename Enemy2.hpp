#ifndef Enemy2_HPP
#define Enemy2_HPP
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class Enemy2: public Turret {
public:
    Enemy2(float x, float y);
    void CreateBullet() override;
};
#endif
