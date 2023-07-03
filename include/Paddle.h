
#ifndef PADDLE_H
#define PADDLE_H
#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>


class Paddle
{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddleShape;

        float m_paddleMoveSpeed;
        float m_paddleDirectionY;


        //Functions
        void initPaddleProperties();


    public:
        Paddle(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        float getPaddleTimer();
        void setPaddleTimer(float time);

        void moveUp();
        void moveDown();
        void idleMove();

        void update(float deltaTime);
        void render(sf::RenderTarget& target);



};


#endif // !PADDLE_H
