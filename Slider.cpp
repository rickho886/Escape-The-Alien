#include "Slider.hpp"
#include "GameEngine.hpp"
#include <stdio.h>
#include <algorithm>

Slider::Slider(float x, float y, float w, float h) :
	ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", x, y),
	Bar("stage-select/bar.png", x, y, 190, h),
	End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
	End2("stage-select/end.png", x + 190, y + h / 2, 0, 0, 0.5, 0.5) {
	Position.x += w;
	Position.y += h / 2;
	Anchor = Engine::Point(0.5, 0.5);
}

void Slider::Draw() const {
	Bar.Draw();
	End1.Draw();
	End2.Draw();
    Engine::ImageButton::Draw();
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
	OnValueChangedCallback = onValueChangedCallback;
}
void Slider::SetValue(float value) {
    if(OnValueChangedCallback) OnValueChangedCallback(value);
}
void Slider::OnMouseDown(int button, int mx, int my) {
	Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
    Engine::Point slide = Engine::GameEngine::GetInstance().GetScreenSize();
    if((button & 1 ) && mx >= (Position.x - 220) && mx <= (Position.x + 30) && my >= (Position.y - 20) && my <= (Position.y + 20))
        Down = true;
}
void Slider::OnMouseUp(int button, int mx, int my) {
	Down = false;
}
void Slider::OnMouseMove(int mx, int my) {
    Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
    Engine::Point slide = Engine::GameEngine::GetInstance().GetScreenSize();
    if(Down && mx >= (slide.x/2 - 55) && mx <= (slide.x/2 + 135) && my >= (Position.y - 20) && my <= (Position.y + 20)) {
        float value = (slide.x/2 - 55 - mouse.x) / 190 * -1;
        SetValue(value);
        bmp = imgIn;
        if(mx > Position.x) {
            Position.x = Position.x + (mx - Position.x);
        } else Position.x = Position.x - (Position.x - mx);
    }
    else bmp = imgOut;
}
