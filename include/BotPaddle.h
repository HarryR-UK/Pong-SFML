#ifndef BOTPADDLE_H
#define BOTPADDLE_H
#pragma once

#include <SFML/Graphics.hpp>

class BotPaddle{
    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_paddleShape;

        float m_paddleMoveSpeed;
        float m_paddleDirectionY;
        float m_paddleMoveDelay;

        void initPaddleProperties();

    public:
        BotPaddle(float startX, float startY);

        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        
        void update(float deltaTime, sf::Vector2f ballPos);
        void render(sf::RenderTarget& target);

};


#endif
