#ifndef BALL_H
#define BALL_H
#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include "Paddle.h"

class Ball
{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_ballShape; // sus????

        float m_ballSpeed;
        float m_directionX;
        float m_directionY;
        
        float m_bounceTimer;

        Paddle* m_paddle;

        // Functions
        void initBallProperties(); // wtf?
                                   
        
    public:
        Ball(float startX, float startY, Paddle* paddle);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();

        float getXVelocity();
        float getBounceTimer();
        void setBounceTimer(float time);

        void bounceOnSides();
        void bounceOnTop();
        void missBottom();

        void hitBall();
        void update(float deltaTime);
        void checkBallCollisions(sf::VideoMode videoMode);
        void render(sf::RenderTarget &target);



};

#endif // !BALL_H
