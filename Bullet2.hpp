#ifndef Bullet2_HPP
#define Bullet2_HPP
#include "Bullet.hpp"
class Bullet2 : public Bullet {
public:
	explicit Bullet2(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
};
#endif
