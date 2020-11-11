#ifndef AURAEFFECT_HPP
#define AURAEFFECT_HPP
#include "Sprite.hpp"
#include "PlayScene.hpp"

class AuraEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	AuraEffect(float x, float y);
	void Update(float deltaTime) override;
};
#endif
