#include "PlayScene.hpp"
#include "Enemy1.hpp"
#include "Bullet1.hpp"
#include "AudioHelper.hpp"

Enemy1::Enemy1(float x, float y) :
	Turret("play/enemy-1.png", x, y, 1500, 0.5) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Enemy1::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	getPlayScene()->BulletGroup->AddNewObject(new Bullet1(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
