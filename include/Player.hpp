#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "GameObject.hpp"
#include <string>

class Player : public GameObject
{
public:
    /* Methods */
    Player(SDL_Surface* surf, float vel, std::string name);
    virtual ~Player(){};

    // getter - setter //
    int getHealth();
    void setHealth(int h);
    std::string getName();
    void setName(std::string n);

    virtual void update(float timeSinceLastFrame);

    /* Attributes */
    bool fireLocked;
    int health;
    std::string name;
};

#endif // PLAYER_HPP_INCLUDED
