
#include "../include/Game.h"
#include "../include/Time.h"

Game::Game(Ball& ball, Player1Paddle& p1Paddle)
{
    this->m_ball = &ball;
    this->m_p1Paddle = &p1Paddle;

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
    this->m_ball->update(Time::deltaTime);
    this->m_p1Paddle->update(Time::deltaTime);
}

void Game::updateText()
{
    m_player1Text.setString("0");
    m_player2Text.setString("0");
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->m_player1Text);
    target.draw(this->m_player2Text);
}

void Game::renderBall(sf::RenderTarget &target)
{
    target.draw(this->m_ball->getShape());
}

void Game::renderPaddle(sf::RenderTarget &target)
{
    target.draw(this->m_p1Paddle->getShape());
}


void Game::render()
{
    m_window->clear();

    // Draw objects
    this->renderText(*this->m_window);
    this->renderBall(*this->m_window);
    this->renderPaddle(*this->m_window);
    
    m_window->display();
}

void Game::getInput()
{

    m_p1Paddle->setPaddleTimer(m_p1Paddle->getPaddleTimer() - Time::deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->m_window->close();
    }

    //Paddle movements
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
    {
        this->m_p1Paddle->moveUp();

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->m_p1Paddle->moveDown();
    }
    else
    {
        this->m_p1Paddle->idleMove();
    }
            

    
}

void Game::startTInput()
{
    this->m_inputThread = std::thread (&Game::getInput, this);
}

void Game::updateBallCollisions()
{

    m_ball->setBounceTimer(m_ball->getBounceTimer() - Time::deltaTime);

    // collision on either left or right side
    if(m_ball->getPosition().left < 0 || m_ball->getPosition().left + m_ball->getPosition().width > this->m_videoMode.width && m_ball->getBounceTimer() < 0)
    {
        m_ball->bounceOnSides();
        m_ball->setBounceTimer(0.05f);
    }

    if(m_ball->getPosition().top < 0 || m_ball->getPosition().top + m_ball->getPosition().height > this->m_videoMode.height && m_ball->getBounceTimer() < 0)
    {
        m_ball->bounceOnTop();
        m_ball->setBounceTimer(0.05f);
    }

    if((m_ball->getPosition().intersects(m_p1Paddle->getPosition())) && m_ball->getBounceTimer() < 0)
    {
        int choice = rand() % 2;
        switch(choice)
        {
            case 0:
                m_ball->bounceOnTop();
                m_ball->bounceOnSides();

                break;
            case 1:
                m_ball->bounceOnSides();

                break;
            default:
                break;

        }

        m_ball->setBounceTimer(0.05f);
    }

    /*if(m_ball->getPosition().top + m_ball->getPosition().height > this->m_videoMode.height)
      {
      m_ball->missBottom();
      }*/
}

void Game::startTBall()
{
    this->m_ballThread = std::thread(&Game::updateBallCollisions, this);
}

void Game::startGLoop(){

    while(this->isRunning())
    { 
        // starts the main threads
        this->startTBall();
        this->startTInput();

        Time::initDeltaTime();


        // thread in future???? if ur fucking smart enough, save me
        this->update();


        this->render();
        m_ballThread.join();
        m_inputThread.join();
    }
}
