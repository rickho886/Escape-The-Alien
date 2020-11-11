#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "AuraEffect.hpp"
#include "AudioHelper.hpp"

PlayScene* AuraEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
AuraEffect::AuraEffect(float x, float y) : Sprite("play/aura/0.png", x, y, 100, 100), timeTicks(0) {
	for (int i = 0; i <= 18; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/aura/" + std::to_string(i) + ".png"));
	}
	AudioHelper::PlayAudio("aura.wav");
}
void AuraEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
