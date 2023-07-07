#ifndef BOTPADDLE_H
#define BOTPADDLE_H
#pragma once

#include <SFML/Graphics.hpp>

class BotPaddle{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddleShape;
        sf::RectangleShape m_originPoint;

        float m_paddleMoveSpeed;
        float m_paddleDirectionY;

        void initPaddleProperties();

    public:
        BotPaddle(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        
        void update(float deltaTime, float ballYVelocity, sf::Vector2f ballPosition);
        void render(sf::RenderTarget& target);

};


#endif
