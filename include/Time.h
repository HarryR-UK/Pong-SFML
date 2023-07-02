#ifndef TIME_H
#define TIME_H
#pragma once


#include<iostream>
#include<SFML/System.hpp>

#include "../include/Global.h"

class Time{
    public:
        static void initDeltaTime();
        inline static float deltaTime;
        inline static sf::Clock clock;

        static void showFPS();

        
    private:
        static constexpr float multiplier = TIME_DELTATIME_MULTIPLIER;


};



#endif // !TIME_H
