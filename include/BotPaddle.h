#ifndef BOTPADDLE_H
#define BOTPADDLE_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Time.h"


class BotPaddle{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddleShape;
        sf::RectangleShape m_originPoint;

        float m_paddleMoveSpeed;
        float m_paddleDirectionY;

        float m_botPaddleSpeedChangeTimer;

        void initPaddleProperties();

    public:
        BotPaddle(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        
        void update(float deltaTime, float ballYVelocity, sf::Vector2f ballPosition);
        void render(sf::RenderTarget& target);
        void checkPaddleCollisions(sf::VideoMode videoMode);

        void setPaddleSpeed(float newSpeed);
        float getPaddleSpeed();

        void changePaddleSpeed();
        void resetSpeed();

        sf::FloatRect nextPos;

};


#endif
