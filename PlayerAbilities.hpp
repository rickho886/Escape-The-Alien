#ifndef PLAYERABILITIES_HPP
#define PLAYERABILITIES_HPP
#include "Sprite.hpp"
#include "Collider.hpp"
#include "PlayerShip.hpp"
#include <random>

class PlayScene;
class PlayerShip;
class PlayerAbilities : public Engine::Sprite {
protected:
    int ability;
    PlayScene* getPlayScene();
    virtual void OnExplode(PlayerShip* player);
public:
    explicit PlayerAbilities(std::string img, Engine::Point position, int ability);
    void Update(float deltaTime) override;
};
#endif
