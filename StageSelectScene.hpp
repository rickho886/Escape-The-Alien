#ifndef STAGESELECTSCENE_HPP
#define STAGESELECTSCENE_HPP
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class StageSelectScene final : public Engine::IScene {
private:
    int highscore;
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
	explicit StageSelectScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage);
	void SettingOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif
