#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "Player.hpp"
#include "Bullet.hpp"

const int playerVelocity = 1.0f;
const int bulletVelocity = 1.0f;
const int timeSinceLastFrame = 0.25f;
bool fireLocked = false;

SDL_Surface* bulletSurf;

Player* michel = NULL;
Player* amelie = NULL;

Bullet* bulletsPlayer01[3] = {NULL, NULL, NULL};
Bullet* bulletsPlayer02[3] = {NULL, NULL, NULL};

void fireBullet(std::string owner)
{
    if (owner == "Michel")
    {
        for (int i = 0; i<3; i++)
        {
            if (bulletsPlayer01[i] == NULL || !bulletsPlayer01[i]->active)
            {
                if (bulletsPlayer01[i] == NULL) bulletsPlayer01[i] = new Bullet(bulletSurf, bulletVelocity, 10);
                bulletsPlayer01[i]->active = true;

                float x = michel->getPos().x;
                float y = michel->getPos().y;
                bulletsPlayer01[i]->setPos(x, y);
                bulletsPlayer01[i]->direction = michel->direction;

                return;
            }
        }
    }
//    else if (owner == "Amelie")
//    {
//
//    }
}


SDL_Surface *load_image( std::string filename )
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

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    /* Setup WalkAndShoot */
    SDL_Surface* bgSurf = load_image("../../resources/bg.png");
    SDL_Surface* player01Surf = load_image("../../resources/player01.png");
    SDL_Surface* player02Surf = load_image("../../resources/player02.png");
    bulletSurf = load_image("../../resources/bullet.png");

    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;

    // setup players //
    amelie = new Player(player01Surf, playerVelocity, "Amelie");
    michel = new Player(player02Surf, playerVelocity, "Michel");

    michel->setPos(0.0f, 0.0f);
    amelie->setPos(320.0f, 240.0f);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
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

            /* Collision Detection */

            /*                    */

            Uint8 *keystates = SDL_GetKeyState( NULL );

            /* Quit */
            if (keystates[SDLK_ESCAPE]) done = true;
            /*      */

            /* Player 01 - Input */
            // Keydown
            if (keystates[SDLK_SPACE] && !fireLocked) // Shoot
            {
                fireBullet("Michel");
                fireLocked = true;
            }
            if (keystates[SDLK_w]) // Up
            {
                michel->goUp = true;
                michel->goDown = false;
            }
            else if (keystates[SDLK_s]) // Down
            {
                michel->goDown = true;
                michel->goUp = false;
            }
            if (keystates[SDLK_a]) // Left
            {
                michel->goLeft = true;
                michel->goRight = false;
            }
            else if (keystates[SDLK_d]) // Right
            {
                michel->goRight = true;
                michel->goLeft = false;
            }
            // Keyup
            if (!keystates[SDLK_SPACE]) // Shoot
            {
                fireLocked = false;
            }
            if (!keystates[SDLK_w]) // Up
            {
                michel->goUp = false;
            }
            if (!keystates[SDLK_s]) // Down
            {
                michel->goDown = false;
            }
            if (!keystates[SDLK_a]) // Left
            {
                michel->goLeft = false;
            }
            if (!keystates[SDLK_d]) // Right
            {
                michel->goRight = false;
            }
            /*          */

            /* Player 02 - Input*/
            // Keydown
            if (keystates[SDLK_UP]) // Up
            {
                amelie->goUp = true;
                amelie->goDown = false;
            }
            else if (keystates[SDLK_DOWN]) // Down
            {
                amelie->goDown = true;
                amelie->goUp = false;
            }
            if (keystates[SDLK_LEFT]) // Left
            {
                amelie->goLeft = true;
                amelie->goRight = false;
            }
            else if (keystates[SDLK_RIGHT]) // Right
            {
                amelie->goRight = true;
                amelie->goLeft = false;
            }

            // Keyup
            if (!keystates[SDLK_UP]) // Up
            {
                amelie->goUp = false;
            }
            if (!keystates[SDLK_DOWN]) // Down
            {
                amelie->goDown = false;
            }
            if (!keystates[SDLK_LEFT]) // Left
            {
                amelie->goLeft = false;
            }
            if (!keystates[SDLK_RIGHT]) // Right
            {
                amelie->goRight = false;
            }
            /*                  */


        } // end of message processing


        // Updating
        amelie->update(timeSinceLastFrame);
        michel->update(timeSinceLastFrame);

        for (int i=0; i<3; i++)
        {
            if(bulletsPlayer01[i] != NULL)
            {
                if (bulletsPlayer01[i]->active)
                {
                    bulletsPlayer01[i]->update(timeSinceLastFrame);
                }
            }
        }
        //
        // DRAWING STARTS HERE

        // clear screen
        SDL_BlitSurface(bgSurf, NULL, screen, &bgRect);
        amelie->draw(screen);
        michel->draw(screen);

        for (int i=0; i<3; i++)
        {
            if(bulletsPlayer01[i] != NULL)
            {
                if (bulletsPlayer01[i]->active)
                {
                    bulletsPlayer01[i]->draw(screen);
                }
            }
        }


        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(player01Surf);
    SDL_FreeSurface(player02Surf);
    SDL_FreeSurface(bgSurf);
    SDL_FreeSurface(bulletSurf);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
