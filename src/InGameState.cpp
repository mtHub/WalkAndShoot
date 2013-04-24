#include "InGameState.hpp"
#include "Player.hpp"
#include "BulletManager.hpp"
#include <SDL/SDL_image.h>

InGameState::InGameState()
{
    active = false;
    playerVelocity = 1.0f;
    bulletVelocity = 1.0f;
    bulletDamage = 10;
    player01Surf = NULL;
    player02Surf = NULL;
    bgSurf = NULL;
    bulletSurf = NULL;
    player01 = NULL;
    player02 = NULL;
    bulletManager = NULL;
}

bool InGameState::init()
{
    /* Load images */
    bgSurf = load_image("../../../resources/bg.png");
    player01Surf = load_image("../../../resources/player01.png");
    player02Surf = load_image("../../../resources/player02.png");
    bulletSurf = load_image("../../../resources/bullet.png");

    if(bgSurf==NULL || player01Surf==NULL || player02Surf==NULL || bulletSurf==NULL)
    {
        return false;
    }

    /* Init players */
    player02 = new Player(player01Surf, playerVelocity, "Michel");
    player01 = new Player(player02Surf, playerVelocity, "Amelie");

    bulletManager = new BulletManager(bulletSurf, bulletVelocity, bulletDamage);

    return true;
}

void InGameState::finalize()
{
    SDL_FreeSurface(bgSurf);
    SDL_FreeSurface(player01Surf);
    SDL_FreeSurface(player02Surf);
    SDL_FreeSurface(bulletSurf);
}

void InGameState::start()
{
    active = true;
}

void InGameState::pause()
{
}

void InGameState::update(float timeSinceLastFrame)
{
    Uint8 *keystates = SDL_GetKeyState( NULL );

    /* Quit */
//    if (keystates[SDLK_ESCAPE]) done = true;
    /*      */

    /* Player 01 - Input */
    // Keydown
    if (keystates[SDLK_SPACE] && !player01->fireLocked) // Shoot
    {
        //fire
        bulletManager->fireBullet(player01);
        player01->fireLocked = true;
    }
    if (keystates[SDLK_w]) // Up
    {
        player01->goUp = true;
        player01->goDown = false;
    }
    else if (keystates[SDLK_s]) // Down
    {
        player01->goDown = true;
        player01->goUp = false;
    }
    if (keystates[SDLK_a]) // Left
    {
        player01->goLeft = true;
        player01->goRight = false;
    }
    else if (keystates[SDLK_d]) // Right
    {
        player01->goRight = true;
        player01->goLeft = false;
    }
    // Keyup
    if (!keystates[SDLK_SPACE]) // Shoot
    {
        player01->fireLocked = false;
    }
    if (!keystates[SDLK_w]) // Up
    {
        player01->goUp = false;
    }
    if (!keystates[SDLK_s]) // Down
    {
        player01->goDown = false;
    }
    if (!keystates[SDLK_a]) // Left
    {
        player01->goLeft = false;
    }
    if (!keystates[SDLK_d]) // Right
    {
        player01->goRight = false;
    }
    /*          */

    /* Player 02 - Input*/
    // Keydown
    if (keystates[SDLK_UP]) // Up
    {
        player02->goUp = true;
        player02->goDown = false;
    }
    else if (keystates[SDLK_DOWN]) // Down
    {
        player02->goDown = true;
        player02->goUp = false;
    }
    if (keystates[SDLK_LEFT]) // Left
    {
        player02->goLeft = true;
        player02->goRight = false;
    }
    else if (keystates[SDLK_RIGHT]) // Right
    {
        player02->goRight = true;
        player02->goLeft = false;
    }

    // Keyup
    if (!keystates[SDLK_UP]) // Up
    {
        player02->goUp = false;
    }
    if (!keystates[SDLK_DOWN]) // Down
    {
        player02->goDown = false;
    }
    if (!keystates[SDLK_LEFT]) // Left
    {
        player02->goLeft = false;
    }
    if (!keystates[SDLK_RIGHT]) // Right
    {
        player02->goRight = false;
    }
    /*                  */

    bulletManager->update(timeSinceLastFrame);
    player01->update(timeSinceLastFrame);
    player02->update(timeSinceLastFrame);
}

void InGameState::draw(SDL_Surface* screen)
{
    // Draw background
    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;
    SDL_BlitSurface(bgSurf, NULL, screen, &bgRect);
    // Draw bullets
    bulletManager->draw(screen);
    // Draw players
    player01->draw(screen);
    player02->draw(screen);
}

SDL_Surface* InGameState::load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}
