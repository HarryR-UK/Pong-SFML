#include <iostream>

#include "../include/Game.h"
#include "../include/Ball.h"
#include "../include/Paddle.h"
#include "../include/BotPaddle.h"

int main(int argc, char* argv[])
{
    std::srand(static_cast<unsigned>(time(NULL)));

    BotPaddle botPaddle((1920.f * 0.1f)/ 1.013f, (1080.f * 0.7f) / 2.f - 150.f);
    Paddle paddle((1920.f * 0.1f)/ 1.013f, (1080.f * 0.7f) / 2.f - 150.f);

    Ball ball((1920.f * 0.2f)/2.f - 5, 0.f);

    // sets ball position to half the screen width then half the size of the ball as origin = 0,0
    Game game(&ball, &paddle, &botPaddle);
}
