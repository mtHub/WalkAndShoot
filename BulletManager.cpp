#include "BulletManager.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

BulletManager::BulletManager(SDL_Surface* bulletSurf, float bulletVelocity, int damage)
{
    this->bulletSurf = bulletSurf;
}

void BulletManager::fireBullet(Player* player)
{
    if (bullets.size() == 0)
    {
        Bullet* bullet = new Bullet(bulletSurf, bulletVelocity, damage);
        bullet->owner = player;
        bullet->active = true;
        bullet->direction = player->direction;
        bullet->pos = player->pos;
        bullets.push_back(bullet);
    }
    else
    {
        for(int i=0; i<bullets.size(); i++)
        {
            if(!bullets[i]->active)
            {
                bullets[i]->active = true;
                bullets[i]->owner = player;
                bullets[i]->direction = player->direction;
                bullets[i]->pos = player->pos;
                return;
            }
        }

        Bullet* bullet = new Bullet(bulletSurf, bulletVelocity, damage);
        bullet->owner = player;
        bullet->active = true;
        bullet->direction = player->direction;
        bullet->pos = player->pos;
        bullets.push_back(bullet);

    }
}

void BulletManager::update(float timeSinceLastFrame)
{
    for(int i=0; i<bullets.size(); i++)
    {
        bullets[i]->update(timeSinceLastFrame);
    }
}

void BulletManager::draw(SDL_Surface* screen)
{
    for(int i=0; i<bullets.size(); i++)
    {
        bullets[i]->draw(screen);
    }
}
