
#include "../include/Game.h"
#include <thread>

Game::Game(Ball* ball, Paddle* paddle, BotPaddle* botPaddle) 
{
    
    this->m_ball = ball;
    this->m_paddle = paddle;
    this->m_botPaddle = botPaddle;

    // Initiations
    initVariables();

    initWindow();
    initFont();
    initText();

    // starts the game loop
    startGLoop();
}

Game::~Game()
{
    delete m_window;
}

void Game::initVariables()
{
    m_window = nullptr;

    m_screenHeight = sf::VideoMode::getDesktopMode().height;
    m_screenWidth = sf::VideoMode::getDesktopMode().width;
}

void Game::initWindow()
{
    m_videoMode.width = m_screenWidth * 0.7;
    m_videoMode.height = m_screenHeight * 0.7;

    m_window = new sf::RenderWindow(m_videoMode, "PONG", sf::Style::Close | sf::Style::None);
}

void Game::initFont()
{
    if(!m_gameFont.loadFromFile("../resources/fonts/Minecraft.ttf"))
    {
        std::cerr << "ERROR::GAME::INITFONT::Failed to load Minecraft Font!" << '\n';
    }
}

void Game::initText()
{
    // Player 1
    m_player1Text.setFont(m_gameFont);
    m_player1Text.setCharacterSize(50);
    m_player1Text.setFillColor(sf::Color::White);
    m_player1Text.setString("NONE");
    m_player1Text.setPosition((0.25 * m_videoMode.width) - 0.5, 0);
    
    // Player 2
    m_player2Text.setFont(m_gameFont);
    m_player2Text.setCharacterSize(50);
    m_player2Text.setFillColor(sf::Color::White);
    m_player2Text.setString("NONE");
    m_player2Text.setPosition((0.75 * m_videoMode.width) + 0.5, 0);

}

const bool Game::isRunning() const
{
    return this->m_window->isOpen();
}

void Game::pollEvents()
{
    while(m_window->pollEvent(m_event))
    {
        switch(m_event.type)
        {
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    this->pollEvents();

    this->updateText();
    m_ball->update(Time::deltaTime);
    m_paddle->update(Time::deltaTime);
    m_botPaddle->update(Time::deltaTime,m_ball->getYVelocity(), m_ball->getShapePos());

    m_ball->checkBallCollisions(m_videoMode);
    // this->updateBallCollisions();
}

void Game::updateText()
{
    m_player1Text.setString("0");
    m_player2Text.setString("0");
}

void Game::updateBallCollisions()
{
    while(isRunning())
    {
        if(m_ball->nextPos.intersects(m_paddle->getPosition()) || m_ball->nextPos.intersects(m_botPaddle->getPosition()))
        {
            switch(m_paddleHitRandomChoice)
            {
                case 0:
                    m_ball->bounceOnSides();
                    break;
                case 1:
                    m_ball->bounceOnTop();
                    m_ball->bounceOnSides();
                    break;
                default:
                    std::cout << "ERROR GAME::UPDATEBALLCOLLISIONS paddle hit random choice not working" << '\n';

            }
        }

    }
}


void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->m_player1Text);
    target.draw(this->m_player2Text);
}



void Game::render()
{
    m_window->clear();

    // Draw objects
    this->renderText(*this->m_window);
    m_ball->render(*this->m_window);
    m_paddle->render(*this->m_window);
    m_botPaddle->render(*this->m_window);
    
    m_window->display();
}

void Game::getInput()
{
    while(isRunning())
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->m_window->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_paddle->moveUp();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_paddle->moveDown();
        }
        else{
            m_paddle->idleMove();
        }


    }


    
}


void Game::startGLoop(){

    m_inputThread = std::thread(&Game::getInput, this);
    m_ballCollisionsThread = std::thread(&Game::updateBallCollisions, this);
    while(this->isRunning())
    { 

        m_paddleHitRandomChoice = rand() % 2;

        Time::initDeltaTime();

        // thread in future???? if ur fucking smart enough, save me
        this->update();


        this->render();
    }
    m_inputThread.join();
    m_ballCollisionsThread.join();
}
