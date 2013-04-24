#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "GameObject.hpp"

class Player;

class Bullet : public GameObject
{
public:
    /* Methods */
    Bullet(SDL_Surface* surf, float vel, int damage);
    virtual ~Bullet(){};

    virtual void update(float timeSinceLastFrame);

    /* Attributes */
    bool active;
    int damage;
    Player* owner;
};

#endif // BULLET_HPP_INCLUDED
