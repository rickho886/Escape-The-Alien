#ifndef SETTINGSCENE_HPP
#define SETTINGSCENE_HPP
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class SettingScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
	explicit SettingScene() = default;
	void Initialize() override;
	void BackOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif
