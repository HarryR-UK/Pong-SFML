#include <iostream>

#include "../include/Game.h"
#include "../include/Ball.h"
#include "../include/Paddle.h"
#include "../include/BotPaddle.h"

int main(int argc, char* argv[])
{
    std::srand(static_cast<unsigned>(time(NULL)));

    // appropriate coordinates for each paddle on the screen
    BotPaddle botPaddle((1920.f * 0.005f)/ 1.013f, (1080.f * 0.7f) / 2.f - 150.f);
    Paddle paddle((1920.f * 0.7f)/ 1.013f, (1080.f * 0.7f) / 2.f - 150.f);

    Ball ball((1920.f * 0.5f)/2.f - 5, 100.f);

    Game game(&ball, &paddle, &botPaddle);
}
