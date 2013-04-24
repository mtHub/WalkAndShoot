#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include <SDL/SDL.h>
#include "Vector2D.hpp"

class GameObject
{
public:
    /* Methods */
    GameObject(SDL_Surface* surf, float vel);
    virtual ~GameObject(){};

    // getter - setter //
    Vector2D getPos();
    void setPos(float x, float y);
    void setPos(Vector2D v);
    float getVelocity();
    void setVelocity(float v);
    SDL_Rect* getRect();

    virtual void update(float timeSinceLastFrame);
    void draw(SDL_Surface* screen);

    /* Attributes */
    SDL_Rect rect;
    SDL_Surface* surf;
    Vector2D pos, direction;
    float velocity;
    bool goLeft;
    bool goRight;
    bool goUp;
    bool goDown;
};

#endif // GAMEOBJECT_HPP_INCLUDED
