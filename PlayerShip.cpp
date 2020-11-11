#include <allegro5/allegro_primitives.h>
#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "PlayerShip.hpp"
#include "ExplosionEffect.hpp"
#include "AuraEffect.hpp"
#include "AudioHelper.hpp"

PlayScene* PlayerShip::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
PlayerShip::PlayerShip(std::string imgPlayerShip, float x, float y, float radius, float coolDown) :
	Sprite(imgPlayerShip, x, y), coolDown(coolDown){
	CollisionRadius = radius;
	immortal = 0;
	pre_immortal = 0;
	ticks_immortal = 0;
	ticks_lowhp = 0;
}
void PlayerShip::Update(float deltaTime) {
    Sprite::Update(deltaTime);
	Position = Engine::GameEngine::GetInstance().GetMousePosition();
    if(immortal == 1) {
        ticks_immortal += deltaTime;
        getPlayScene()->EffectGroup->AddNewObject(new AuraEffect(Position.x, Position.y));
        if(ticks_immortal > 4) {
            immortal = 0;
            ticks_immortal = 0;
        }
    }
    if(hp <= 5) {
        ticks_lowhp += deltaTime;
        if(ticks_lowhp > 0.6) {
            ticks_lowhp = 0;
            AudioHelper::PlayAudio("low-hp.wav");
        }
    }
}
void PlayerShip::Draw() const {
	if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}
}

void PlayerShip::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
}

void PlayerShip::PreAbility(int pre_ability) {
    if(pre_ability == 0) pre_immortal = 1;
    getPlayScene()->ImmortalCount(pre_immortal);
}

void PlayerShip::SpecialAbility(int ability) {
    if(pre_immortal == 1 && ability == 0) {
        immortal = 1;
        pre_immortal = 0;
    }
}


void PlayerShip::Hit(float damage) {
    if(!immortal) hp -= damage;
	getPlayScene()->LifeUpdate(hp);
	OnExplode();
    if (hp <= 0) {
		OnExplode();
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->PlayerShipGroup->RemoveObject(objectIterator);
	}
}
