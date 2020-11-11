#include <allegro5/allegro_primitives.h>
#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "ExplosionEffect.hpp"
#include "PlayerShip.hpp"
float direction[8][2] = {{0,1}, {1,0}, {0, -1}, {-1, 0}, {1,1}, {-1,-1}, {1,-1}, {-1,1}};
PlayScene* Turret::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Turret::Turret(std::string imgTurret, float x, float y, float radius, float coolDown) :
	Sprite(imgTurret, x, y), coolDown(coolDown) {
	CollisionRadius = radius;
}
void Turret::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
    if(Position.x < 30 || (Position.x > Engine::GameEngine::GetInstance().GetScreenSize().x - 30) || Position.y < 30 || Position.y > Engine::GameEngine::GetInstance().GetScreenSize().y - 30 || start == 1) {
        start = 0;
        dir = rand() % 8;
    }
	Position.x += direction[dir][0];
	Position.y += direction[dir][1];
	if (!Enabled)
		return;
	if (Target) {
		Engine::Point diff = Target->Position - Position;
		if (diff.Magnitude() > CollisionRadius) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
	}
	if (!Target) {
		for (auto& it : scene->PlayerShipGroup->GetObjects()) {
            Engine::Point diff = it->Position - Position;
            if (diff.Magnitude() <= CollisionRadius) {
                Target = dynamic_cast<PlayerShip*>(it);
                Target->lockedTurrets.push_back(this);
                lockedTurretIterator = std::prev(Target->lockedTurrets.end());
                break;
            }
		}
	}
	if (Target) {
		Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
		Engine::Point NTargetRotation = (Target->Position - Position).Normalize();
		float maxRotateRadian = rotateRadian * deltaTime;
		float cosTheta = originRotation.Dot(NTargetRotation);
		if (cosTheta > 1) cosTheta = 1;
		else if (cosTheta < -1) cosTheta = -1;
		float radian = acos(cosTheta);
		Engine::Point rotation;
		if (abs(radian) <= maxRotateRadian)
			rotation = NTargetRotation;
		else
			rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * NTargetRotation) / radian;
		Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
		reload -= deltaTime;
		if (reload <= 0) {
			reload = coolDown;
			CreateBullet();
		}
	}
}
void Turret::Draw() const {
	if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}
}

void Turret::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
}
