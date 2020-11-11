#include "PlayScene.hpp"
#include "Bullet2.hpp"
#include "Enemy2.hpp"
#include "AudioHelper.hpp"

Enemy2::Enemy2(float x, float y) :
	Turret("play/enemy-2.png", x, y, 1500, 0.5) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Enemy2::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	getPlayScene()->BulletGroup->AddNewObject(new Bullet2(Position + normalized * 36 - normal * 6, diff, rotation, this));
	AudioHelper::PlayAudio("laser.wav");
}
