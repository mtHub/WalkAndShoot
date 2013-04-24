#ifndef BULLETMANAGER_HPP_INCLUDED
#define BULLETMANAGER_HPP_INCLUDED

#include <vector>
#include <SDL/SDL.h>

class Bullet;
class Player;

class BulletManager
{
public:
    BulletManager(SDL_Surface* bulletSurf, float bulletVelocity, int damage);
    ~BulletManager(){};

    void fireBullet(Player* player);
    void update(float timeSinceLastFrame);
    void draw(SDL_Surface* screen);

private:
    float bulletVelocity;
    int damage;
    SDL_Surface* bulletSurf;
    std::vector<Bullet*> bullets;
};

#endif // BULLETMANAGER_HPP_INCLUDED
