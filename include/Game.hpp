#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SDL/SDL.h>
#include "InGameState.hpp"

class Game
{
public:
    Game(int screenX, int screenY);
    ~Game(){};

    bool init();
    void start();
    void update();
    void draw();
    void handleEvents();

private:
    bool done;
    int screenX, screenY;
    SDL_Surface* screen;
    InGameState* inGameState;
};

#endif // GAME_HPP_INCLUDED
