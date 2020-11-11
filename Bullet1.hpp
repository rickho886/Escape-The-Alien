#ifndef Bullet1_HPP
#define Bullet1_HPP
#include "Bullet.hpp"
class Bullet1 : public Bullet {
public:
	explicit Bullet1(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
};
#endif
