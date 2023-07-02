
#ifndef PLAYER1PADDLE_H
#define PLAYER1PADDLE_H
#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player1Paddle
{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddleShape;

        float m_paddleMoveSpeed;
        float m_paddleDirectionY;
        float m_paddleTimer;

        //Functions
        void initPaddleProperties();


    public:
        Player1Paddle(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        float getPaddleTimer();
        void setPaddleTimer(float time);

        void moveUp();
        void moveDown();
        void idleMove();

        void update(float deltaTime);



};


#endif // !PLAYER1PADDLE_H
