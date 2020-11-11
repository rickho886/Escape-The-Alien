#include "Bullet2.hpp"

Bullet2::Bullet2(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-2.png", 800, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
