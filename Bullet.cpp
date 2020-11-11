#include "Sprite.hpp"
#include "Collider.hpp"
#include "Turret.hpp"
#include "Bullet.hpp"
#include "LOG.hpp"
#include "PlayerShip.hpp"
#include "GameEngine.hpp"

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Bullet::OnExplode(PlayerShip* playership) {
}
Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}

void Bullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();

	for (auto& it : scene->PlayerShipGroup->GetObjects()) {
		PlayerShip* playership = dynamic_cast<PlayerShip*>(it);
		if (!playership->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, playership->Position, playership->CollisionRadius)) {
			OnExplode(playership);
			playership->Hit(damage);
			getPlayScene()->TimeCounter(-1);
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
}
