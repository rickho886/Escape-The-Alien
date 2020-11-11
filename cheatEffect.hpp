/*#ifndef CHEATEFFECT_HPP
#define CHEATFFECT_HPP
#include "Sprite.hpp"
#include "PlayScene.hpp"

class cheatEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	cheatEffect(float x, float y);
	void Update(float deltaTime) override;
};
#endif*/
