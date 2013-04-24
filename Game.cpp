#include "Game.hpp"

Game::Game(int screenX, int screenY)
{
    done = false;
    this->screenX = screenX;
    this->screenY = screenY;
    screen = NULL;
    inGameState = NULL;
}

bool Game::init()
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return false;
    }

    /* Init InGameState */
    inGameState = new InGameState();
    if (!inGameState->init()) return false;
    inGameState->start();

    return true;
}

void Game::start()
{
    update();
}

void Game::update()
{
    float timeSinceLastFrame = 0.0f;
    float oldTime = 0.0f;
    float newTime = 0.0f;

    while (!done)
    {
        handleEvents();

        if (inGameState != NULL)
        {
            if (inGameState->active)
            {
                inGameState->update(timeSinceLastFrame);
            }
        }
        draw();
    }
}

void Game::draw()
{
    if (inGameState != NULL)
    {
        if (inGameState->active)
        {
            inGameState->draw(screen);
        }
    }
    SDL_Flip(screen);
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
        case SDL_QUIT:
            done = true;
            break;
        }
    }
}
