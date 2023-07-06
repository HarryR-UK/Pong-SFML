#include "../include/BotPaddle.h"

void BotPaddle::initPaddleProperties()
{
    m_paddleMoveSpeed = 5;
    m_paddleDirectionY = 0.f;
    m_paddleMoveDelay = 0.7f;
}

BotPaddle::BotPaddle(float startX, float startY)
{
    this->initPaddleProperties();

    m_position.x = startX;
    m_position.y = startY;

    m_paddleShape.setSize(sf::Vector2f(15.f, 150.f));
    m_paddleShape.setFillColor(sf::Color::White);
    m_paddleShape.setPosition(m_position);

}

sf::FloatRect BotPaddle::getPosition()
{
    return m_paddleShape.getGlobalBounds();
}

sf::RectangleShape BotPaddle::getShape()
{
    return m_paddleShape;
}

void BotPaddle::update(float deltaTime, sf::Vector2f ballPos)
{
    m_position.y += ballPos.y * m_paddleMoveDelay * deltaTime;
    m_paddleShape.setPosition(m_position);
}

void BotPaddle::render(sf::RenderTarget &target)
{
    target.draw(m_paddleShape);
}
