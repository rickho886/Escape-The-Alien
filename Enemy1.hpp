#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class Enemy1: public Turret {
public:
    Enemy1(float x, float y);
	void CreateBullet() override;
};
#endif
