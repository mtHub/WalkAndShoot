#include "GameObject.hpp"

GameObject::GameObject(SDL_Surface* surf, float vel)
{
    this->surf = surf;
    setPos(0,0);
    direction = Vector2D(0, -1);
    velocity = vel;
    goUp = false;
    goDown = false;
    goLeft = false;
    goRight = false;
}

Vector2D GameObject::getPos()
{
    return pos;
}

void GameObject::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
    rect.x = pos.x;
    rect.y = pos.y;
}

void GameObject::setPos(Vector2D v)
{
    pos = v;
    rect.x = pos.x;
    rect.y = pos.y;
}

float GameObject::getVelocity()
{
    return velocity;
}

void GameObject::setVelocity(float v)
{
    if (v>=0) velocity = v;
}

SDL_Rect* GameObject::getRect()
{
    return &rect;
}

void GameObject::update(float timeSinceLastFrame)
{
}

void GameObject::draw(SDL_Surface* screen)
{
    SDL_Rect blitRect = rect;
    // Center Rect
    blitRect.x -= surf->w/2;
    blitRect.y -= surf->h/2;
    SDL_BlitSurface(surf, NULL, screen, &blitRect);
}
