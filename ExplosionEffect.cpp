#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "ExplosionEffect.hpp"
#include "AudioHelper.hpp"

PlayScene* ExplosionEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
ExplosionEffect::ExplosionEffect(float x, float y) : Sprite("play/explo/explosion-1.png", x, y, 60, 60), timeTicks(0) {
	for (int i = 1; i <= 39; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/explo/explosion-" + std::to_string(i) + ".png"));
	}
	AudioHelper::PlayAudio("explosion.wav");
}
void ExplosionEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
