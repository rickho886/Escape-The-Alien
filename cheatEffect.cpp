/*#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "cheatEffect.hpp"
#include "AudioHelper.hpp"

PlayScene* cheatEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
cheatEffect::cheatEffect(float x, float y) : Sprite("play/ex/0.png", x, y, 100, 100), timeTicks(0) {
	for (int i = 0; i <= 4; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/ex/" + std::to_string(i) + ".png"));
	}
	AudioHelper::PlayAudio("click.ogg");
}
void cheatEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
*/
