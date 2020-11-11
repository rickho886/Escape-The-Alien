#include "Sprite.hpp"
#include "Collider.hpp"
#include "Turret.hpp"
#include "Bullet.hpp"
#include "LOG.hpp"
#include "PlayerShip.hpp"
#include "AudioHelper.hpp"
#include "GameEngine.hpp"

PlayScene* PlayerAbilities::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void PlayerAbilities::OnExplode(PlayerShip* player) {
}

PlayerAbilities::PlayerAbilities(std::string img, Engine::Point position, int ability) :
	Sprite(img, position.x, position.y), ability(ability) {
	CollisionRadius = 4;
}

void PlayerAbilities::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    for (auto& it : scene->PlayerShipGroup->GetObjects()) {
		PlayerShip* playership = dynamic_cast<PlayerShip*>(it);
		if (!playership->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, playership->Position, playership->CollisionRadius)) {
			playership->PreAbility(ability);
			AudioHelper::PlayAudio("bonus.wav");
			getPlayScene()->TimeCounter(10);
			getPlayScene()->PlayerAbilitiesGroup->RemoveObject(objectIterator);
			return;
		}
	}
}
