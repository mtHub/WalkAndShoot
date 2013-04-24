#include "Player.hpp"

Player::Player(SDL_Surface* surf, float vel, std::string name) : GameObject(surf, vel)
{
    this->name = name;
}

int Player::getHealth()
{
    return health;
}

void Player::setHealth(int h)
{
    if (h>=0) health = h;
}

std::string Player::getName()
{
    return name;
}

void Player::setName(std::string n)
{
    name = n;
}

void Player::update(float timeSinceLastFrame)
{
    if (goUp) {direction.x = 0; direction.y = -1;}
    else if (goDown) {direction.x = 0; direction.y = 1;}
    if (goLeft) {direction.x = -1; direction.y = 0;}
    else if (goRight) {direction.x = 1; direction.y = 0;}

    Vector2D newPos = getPos();
    newPos.x += direction.x * velocity;
    newPos.y += direction.y * velocity;
    if (goUp || goDown || goLeft || goRight) {setPos(newPos);}
}
