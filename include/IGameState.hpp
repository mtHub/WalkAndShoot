#ifndef IGAMESTATE_HPP_INCLUDED
#define IGAMESTATE_HPP_INCLUDED

#include <SDL/SDL.h>

class IGameState
{
public:
    virtual bool init() = 0;
    virtual void finalize() = 0;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void update(float timeSinceLastFrame) = 0;
    virtual void draw(SDL_Surface* screen) = 0;
};

#endif // IGAMESTATE_HPP_INCLUDED
