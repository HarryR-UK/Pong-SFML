
#include "../include/Player1Paddle.h"

void Player1Paddle::initPaddleProperties()
{
    m_paddleMoveSpeed = 13;
    m_paddleDirectionY = 0.f;
    m_paddleTimer = 0.10f;
}

Player1Paddle::Player1Paddle(float startX, float startY)
{
    this->initPaddleProperties();

    // Starting position of the paddle
    m_position.x = startX;
    m_position.y = startY;

    m_paddleShape.setSize(sf::Vector2f(15.f, 150.f));
    m_paddleShape.setFillColor(sf::Color::White);
    m_paddleShape.setPosition(m_position);
}

void Player1Paddle::moveUp()
{
    m_paddleDirectionY = -1;
}

void Player1Paddle::moveDown()
{
    m_paddleDirectionY = 1;
}

void Player1Paddle::idleMove()
{
    m_paddleDirectionY = 0;
}

sf::FloatRect Player1Paddle::getPosition()
{
    return m_paddleShape.getGlobalBounds();
}

sf::RectangleShape Player1Paddle::getShape()
{
    return m_paddleShape;
}

float Player1Paddle::getPaddleTimer()
{
    return m_paddleTimer;
}

void Player1Paddle::setPaddleTimer(float time)
{
    m_paddleTimer = time;
}

void Player1Paddle::update(float deltaTime)
{
    m_position.y += m_paddleDirectionY * m_paddleMoveSpeed * deltaTime;

    m_paddleShape.setPosition(m_position);
}
