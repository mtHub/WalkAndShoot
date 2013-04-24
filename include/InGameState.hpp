#ifndef INGAMESTATE_HPP_INCLUDED
#define INGAMESTATE_HPP_INCLUDED

#include "IGameState.hpp"
#include <vector>
#include <string>

class Player;
class BulletManager;

class InGameState : public IGameState
{
public:
    InGameState();
    virtual ~InGameState(){};

    virtual bool init();
    virtual void finalize();
    virtual void start();
    virtual void pause();
    virtual void update(float timeSinceLastFrame);
    virtual void draw(SDL_Surface* screen);

    SDL_Surface *load_image( std::string filename );

    bool active;
protected:
    float playerVelocity;
    float bulletVelocity;
    int bulletDamage;
    Player* player01;
    Player* player02;
    SDL_Surface* player01Surf;
    SDL_Surface* player02Surf;
    SDL_Surface* bgSurf;
    SDL_Surface* bulletSurf;
    BulletManager* bulletManager;
};

#endif // INGAMESTATE_HPP_INCLUDED
