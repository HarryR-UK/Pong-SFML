#ifndef BALL_H
#define BALL_H
#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include "Paddle.h"

class Ball
{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_ballShape; 

        float m_ballSpeed;
        float m_directionX;
        float m_directionY;
        
        float m_bounceTimer;

        sf::Vector2f startPos;

        Paddle* m_paddle;
        sf::Text* p_player1Text;
        sf::Text* p_player2Text;

        float m_scoreTimer;

        // Functions
        void initBallProperties(); // wtf?
                                   
        
    public:
        Ball(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();

        float getYVelocity();
        float getBounceTimer();
        float getBallSpeed();

        void setPlayer1Pointer(sf::Text *player1Text);
        void setPlayer2Pointer(sf::Text *player2Text);
        void setBounceTimer(float time);

        void bounceOnSides();
        void bounceOnTop();
        void missBottom();
        void scoreOnSides();

        void pointToPlayer();
        void pointToBot();


        void hitBall();
        void update(float deltaTime);
        void checkBallCollisions(sf::VideoMode videoMode);
        void render(sf::RenderTarget &target);

        sf::Vector2f getShapePos();

        void resetBallPosition();
        

        sf::FloatRect nextPos;


};

#endif // !BALL_H
