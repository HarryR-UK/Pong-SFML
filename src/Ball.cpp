
#include "../include/Ball.h"

void Ball::initBallProperties()
{
    m_ballSpeed = 7.f;
    m_directionY = 1.f;
    m_directionX = 1.f;
    m_bounceTimer = 0.10f;

}

Ball::Ball(float startX, float startY)
{
    this->initBallProperties();

    m_position.x = startX;
    m_position.y = startY;

    m_ballShape.setSize(sf::Vector2f(10.f, 10.f));
    m_ballShape.setPosition(m_position);
}

sf::FloatRect Ball::getPosition()
{
    return m_ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape()
{
    return m_ballShape;
}


float Ball::getXVelocity()
{
    return m_directionX;
}

float Ball::getBounceTimer()
{
    return m_bounceTimer;
}

void Ball::setBounceTimer(float time)
{
    m_bounceTimer = time;
}

void Ball::bounceOnSides()
{
    m_directionX = -m_directionX;
}

void Ball::bounceOnTop()
{
    m_directionY = -m_directionY;
}

void Ball::missBottom()
{
    m_position.x = 1280.f / 2;
    m_position.y = 0;
}

void Ball::update(float deltaTime)
{
    m_position.x += m_directionX * m_ballSpeed * deltaTime;
    m_position.y += m_directionY * m_ballSpeed * deltaTime;

    m_ballShape.setPosition(m_position);
}