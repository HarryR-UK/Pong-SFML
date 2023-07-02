
#ifndef TIME_H
#define TIME_H
#pragma once


#include<iostream>
#include<SFML/System.hpp>

class Time{
    public:
        static void initDeltaTime();
        inline static float deltaTime;
        inline static sf::Clock clock;

        static void showFPS();

        
    private:
        static constexpr float multiplier = 60.f;


};



#endif // !TIME_H
