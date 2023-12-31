
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
    m_gameOver = false;
    m_playerWins = false;
    m_botWins = false;

    // assigning pointers
    m_pPlayer1Text = &m_player1Text;
    m_pPlayer2Text = &m_player2Text;
    m_ball->setBotPaddle(m_botPaddle);

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
    m_player1Text.setString("0");
    m_player1Text.setPosition((0.25 * m_videoMode.width) - 0.5, 0);
    
    m_ball->setPlayer1Pointer(m_pPlayer1Text);

    
    // Player 2
    m_player2Text.setFont(m_gameFont);
    m_player2Text.setCharacterSize(50);
    m_player2Text.setFillColor(sf::Color::White);
    m_player2Text.setString("0");
    m_player2Text.setPosition((0.75 * m_videoMode.width) + 0.5, 0);

    m_ball->setPlayer2Pointer(m_pPlayer2Text);


    // Game over screen
    

    m_winnertext.setFont(m_gameFont);
    m_winnertext.setCharacterSize(75);
    m_winnertext.setFillColor(sf::Color::White);
    
    m_winnertext.setPosition(sf::Vector2f((m_videoMode.width / 2) - m_winnertext.getCharacterSize() * 2.5, (m_videoMode.height / 2) - m_winnertext.getCharacterSize()));
    
    m_resetText.setFont(m_gameFont);
    m_resetText.setFillColor(sf::Color::White);
    m_resetText.setCharacterSize(30);
    m_resetText.setPosition(sf::Vector2(sf::Vector2f((m_videoMode.width / 2) - m_resetText.getCharacterSize() * 5, (m_videoMode.height / 2) - (m_resetText.getCharacterSize() - 250))));
    
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

    if(!m_gameOver)
    {
        m_ball->update(Time::deltaTime);
        m_paddle->update(Time::deltaTime);
        m_botPaddle->update(Time::deltaTime,m_ball->getYVelocity(), m_ball->getShapePos());

        m_ball->checkBallCollisions(m_videoMode);
        m_paddle->checkPaddleCollisions(m_videoMode);
        m_botPaddle->checkPaddleCollisions(m_videoMode);


        m_playerPoints = std::stoi((std::string) m_player2Text.getString());
        m_botPoints = std::stoi((std::string) m_player1Text.getString());

    }
    else {

        m_resetText.setString("PRESS R TO RESET GAME");

        if(m_playerWins)
        {
            m_winnertext.setString("YOU WIN!");
        }
        else if (m_botWins){
            m_winnertext.setString("YOU LOSE!");
        }
    }

    
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
    if(!m_gameOver)
    {
        this->renderText(*this->m_window);
        m_ball->render(*this->m_window);
        m_paddle->render(*this->m_window);
        m_botPaddle->render(*this->m_window);

    }
    else{
        m_window->draw(m_winnertext);
        m_window->draw(m_resetText);
    }
    
    m_window->display();
}

void Game::checkGameOver()
{
    if(m_playerPoints >= 5)
    {
        m_playerWins = true;
        m_gameOver = true;
    }
    if(m_botPoints >= 5)
    {
        m_botWins = true;
        m_gameOver = true;
    }
}

void Game::restartGame()
{
    m_gameOver = false;
    m_playerWins = false;
    m_botWins = false;

    initText();
    m_ball->resetBallSpeed();
    m_ball->resetBallPosition();

    m_botPaddle->resetSpeed();

}

void Game::getInput()
{
    while(isRunning())
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->m_window->close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_gameOver)
        {
            restartGame();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_paddle->moveUp();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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
        
            Time::initDeltaTime();
            m_paddleHitRandomChoice = rand() % 2;


            this->update();


            this->render();

            this->checkGameOver();

    }
    m_inputThread.join();
    m_ballCollisionsThread.join();
}
