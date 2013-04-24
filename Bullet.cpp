#include "Bullet.hpp"
#include "Player.hpp"

Bullet::Bullet(SDL_Surface* surf, float vel, int damage) : GameObject(surf, vel)
{
    this->damage = damage;
    this->active = false;
    this->owner = NULL;
}

void Bullet::update(float timeSinceLastFrame)
{
    // Update position
    pos += direction * velocity;
    //Update rectangle (needed for blitting)
    rect.x = pos.x;
    rect.y = pos.y;
}
