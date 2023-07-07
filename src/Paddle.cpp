
#include "../include/Paddle.h"

void Paddle::initPaddleProperties()
{
    m_paddleMoveSpeed = 13;
    m_paddleDirectionY = 0.f;
}

Paddle::Paddle(float startX, float startY)
{
    this->initPaddleProperties();

    // Starting position of the paddle
    m_position.x = startX;
    m_position.y = startY;

    m_paddleShape.setSize(sf::Vector2f(15.f, 150.f));
    m_paddleShape.setFillColor(sf::Color::White);
    m_paddleShape.setPosition(m_position);
}

void Paddle::moveUp()
{
    m_paddleDirectionY = -1;
}

void Paddle::moveDown()
{
    m_paddleDirectionY = 1;
}

void Paddle::idleMove()
{
    m_paddleDirectionY = 0;
}

sf::FloatRect Paddle::getPosition()
{
    return m_paddleShape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
    return m_paddleShape;
}

void Paddle::checkPaddleCollisions(sf::VideoMode videoMode)
{
    if(this->nextPos.top < 0)
    {
        this->m_position.y = (0);
    }
    if(this->nextPos.top + m_paddleShape.getSize().y > videoMode.height)
    {
        this->m_position.y =  videoMode.height - m_paddleShape.getGlobalBounds().height;
    }
}

void Paddle::update(float deltaTime)
{
    nextPos = m_paddleShape.getGlobalBounds();
    nextPos.top += m_paddleDirectionY * m_paddleMoveSpeed * deltaTime;

    m_position.y += m_paddleDirectionY * m_paddleMoveSpeed * deltaTime;


    m_paddleShape.setPosition(m_position);
}

void Paddle::render(sf::RenderTarget &target)
{
    target.draw(m_paddleShape);
}
