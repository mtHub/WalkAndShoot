#include "Game.hpp"

int main ( int argc, char** argv )
{
    Game g(640, 480);
    if(!g.init()) return 1;
    g.start();

    return 0;
}
