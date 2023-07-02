#include <iostream>

#include "../include/Game.h"
#include "../include/Ball.h"

int main(int argc, char* argv[])
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Ball ball((1920.f * 0.7f)/2.f - 5, 0.f);

    // sets ball position to half the screen width then half the size of the ball as origin = 0,0
    Game game(&ball);
}
