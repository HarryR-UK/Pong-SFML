
#include "../include/Time.h"
#include <chrono>
#include <cmath>

void Time::initDeltaTime()
{
    Time::deltaTime = Time::clock.restart().asSeconds() * Time::multiplier;
}



