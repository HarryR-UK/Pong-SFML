#include "../include/BotPaddle.h"

#define PADDLE_SPEED_TIMER 50.f

void BotPaddle::initPaddleProperties()
{
    m_paddleMoveSpeed = 5.5f;
    m_paddleDirectionY = 0.f;
    m_botPaddleSpeedChangeTimer = PADDLE_SPEED_TIMER;
}

void BotPaddle::setPaddleSpeed(float newSpeed)
{
    m_paddleMoveSpeed = newSpeed;
}

float BotPaddle::getPaddleSpeed()
{
    return m_paddleMoveSpeed;
}

void BotPaddle::changePaddleSpeed()
{
    m_botPaddleSpeedChangeTimer -= Time::deltaTime;

    if(m_botPaddleSpeedChangeTimer < 0)
    {
        int randSpeed = (rand() % 9) + 3;
        m_paddleMoveSpeed = randSpeed;

        m_botPaddleSpeedChangeTimer = PADDLE_SPEED_TIMER;

    }

}

BotPaddle::BotPaddle(float startX, float startY)
{
    this->initPaddleProperties();

    m_position.x = startX;
    m_position.y = startY;

    m_paddleShape.setSize(sf::Vector2f(15.f, 150.f));
    m_paddleShape.setFillColor(sf::Color::White);
    m_paddleShape.setOrigin(m_paddleShape.getSize().x / 2, m_paddleShape.getSize().y /2);
    m_paddleShape.setPosition(m_position);

    /* DEBUGGING ORIGIN POINT
    m_originPoint.setSize(sf::Vector2f(10,10));
    m_originPoint.setFillColor(sf::Color::Red);
    m_originPoint.setPosition(m_paddleShape.getOrigin());
    m_originPoint.setOrigin(m_originPoint.getSize().x /2, m_originPoint.getSize().y /2);
    */

}

void BotPaddle::checkPaddleCollisions(sf::VideoMode videoMode)
{ 
    if(this->nextPos.top < 0)
    {
        // as out origin is not at half the players height, we need to take this into account with the positioning
        this->m_position.y = (0 + m_paddleShape.getGlobalBounds().height / 2);
    }
    if(this->nextPos.top + m_paddleShape.getSize().y > videoMode.height)
    {
        this->m_position.y =  videoMode.height - m_paddleShape.getGlobalBounds().height /2 ;
    }
}

void BotPaddle::resetSpeed()
{
    m_paddleMoveSpeed = 5.5f;
}

sf::FloatRect BotPaddle::getPosition()
{
    return m_paddleShape.getGlobalBounds();
}

sf::RectangleShape BotPaddle::getShape()
{
    return m_paddleShape;
}

void BotPaddle::update(float deltaTime, float ballYVelocity, sf::Vector2f ballPosition)
{
    changePaddleSpeed();
    nextPos =m_paddleShape.getGlobalBounds();
    nextPos.top += m_paddleDirectionY * m_paddleMoveSpeed * deltaTime;

    (m_paddleShape.getPosition().y < ballPosition.y) ? m_position.y += m_paddleMoveSpeed * deltaTime 
        : m_position.y -= m_paddleMoveSpeed * deltaTime;

    m_paddleShape.setPosition(m_position);
    m_originPoint.setPosition(m_paddleShape.getPosition());

}

void BotPaddle::render(sf::RenderTarget &target)
{
    target.draw(m_paddleShape);
    target.draw(m_originPoint);
}
