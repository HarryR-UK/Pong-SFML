#include "../include/Ball.h"
#include <cstdlib>
#include <sstream>

void Ball::initBallProperties()
{
    m_ballSpeed = 10.f;
    m_directionY = 1.f;
    m_directionX = 1.f;
    m_scoreTimer = 0.5f;

}

Ball::Ball(float startX, float startY) 
{
    this->initBallProperties();

    startPos.x = startX;
    startPos.y = startY;

    m_position.x = startX;
    m_position.y = startY;

    m_ballShape.setSize(sf::Vector2f(10.f, 10.f));
    m_ballShape.setPosition(m_position);
}

float Ball::getBallSpeed()
{
    return m_ballSpeed;
}

sf::FloatRect Ball::getPosition()
{
    return m_ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape()
{
    return m_ballShape;
}


float Ball::getYVelocity()
{
    return m_directionY;
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

void Ball::scoreOnSides()
{
    m_directionY = 1.f;
    m_directionX = 1.f;

    m_position.x = startPos.x;
    m_position.y = startPos.y;

    int newBallSpeed = (rand() % 4) + 1;

    this->m_ballSpeed += newBallSpeed;
    m_botPaddle->setPaddleSpeed(m_botPaddle->getPaddleSpeed() + newBallSpeed + 3);

    m_scoreTimer = 0.5f;
}

void Ball::resetBallPosition()
{

    m_directionY = 1.f;
    m_directionX = 1.f;

    m_position.x = startPos.x;
    m_position.y = startPos.y;
}

void Ball::setBotPaddle(BotPaddle *botPaddle)
{
    m_botPaddle = botPaddle;
}

void Ball::pointToPlayer()
{
    //change Text
    std::string currentPoints = (p_player1Text->getString());
    int newPoints = std::stoi(currentPoints) + 1;
    std::stringstream ss;
    ss << newPoints;
    p_player1Text->setString(ss.str());

    
    

    //reset ball postiion
    this->scoreOnSides();
}


void Ball::pointToBot()
{
    //change Text
    std::string currentPoints = p_player2Text->getString();
    int newPoints = std::stoi(currentPoints) + 1;
    std::stringstream ss;
    ss << newPoints;
    p_player2Text->setString(ss.str());

    //reset ball postiion
    this->scoreOnSides();
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
    
    nextPos = m_ballShape.getGlobalBounds();
    nextPos.left += m_directionX * m_ballSpeed;
    nextPos.top += m_directionY * m_ballSpeed;

    m_position.x += m_directionX * m_ballSpeed * deltaTime;
    m_position.y += m_directionY * m_ballSpeed * deltaTime;
    
    //m_ballShape.move(m_directionX * m_ballSpeed * deltaTime, m_directionY * m_ballSpeed * deltaTime);
    m_ballShape.setPosition(m_position);

    m_scoreTimer -= Time::deltaTime;
}

void Ball::setPlayer1Pointer(sf::Text *player1Text)
{
    this->p_player1Text = player1Text;
}

void Ball::setPlayer2Pointer(sf::Text *player2Text)
{
    this->p_player2Text = player2Text;
}

void Ball::resetBallSpeed()
{
    this->m_ballSpeed = 7;
}

void Ball::checkBallCollisions(sf::VideoMode videoMode)
{

    /*
    // Screen wall collision checking
    if(this->m_ballShape.getPosition().x < 0.f || this->m_ballShape.getPosition().x + m_ballShape.getGlobalBounds().width > videoMode.width)
    {
        //bounceOnSides();
    }
    if(this->m_ballShape.getPosition().y < 0.f || m_ballShape.getPosition().y + m_ballShape.getGlobalBounds().height > videoMode.height)
    {
        //bounceOnTop();
    }
    */

    if(nextPos.left < 0 && m_scoreTimer < 0)
    {
        this->pointToBot();
    }

    if(nextPos.left + m_ballShape.getSize().x > videoMode.width && m_scoreTimer < 0)
    {
        this->pointToPlayer();
    }



    if(nextPos.top < 0 || nextPos.top + m_ballShape.getSize().y > videoMode.height)
    {
        bounceOnTop();
    }


    




}

sf::Vector2f Ball::getShapePos()
{
    return m_position;
}

void Ball::render(sf::RenderTarget &target)
{
    target.draw(m_ballShape);
}
