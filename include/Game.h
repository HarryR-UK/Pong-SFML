
#ifndef GAME_H
#define GAME_H
#include "BotPaddle.h"
#include "Paddle.h"
#pragma once

#include<iostream>
#include<thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../include/Ball.h"
#include "../include/Time.h"

class Game
{
    private:
        
        // Variables
        sf::RenderWindow* m_window;;
        sf::VideoMode m_videoMode;
        sf::Event m_event;


        int m_screenWidth;
        int m_screenHeight;

        int m_paddleHitRandomChoice;

        // Functions
        void initVariables();
        void initWindow();
        void initFont();
        void initText();

        void updateBallCollisions();

        // GUI
        sf::Font m_gameFont;

        sf::Text m_player1Text;
        sf::Text* m_pPlayer1Text;

        sf::Text m_player2Text;
        sf::Text* m_pPlayer2Text;

        int m_playerPoints;
        int m_botPoints;
        

        // Objects
        Ball* m_ball;
        Paddle* m_paddle;
        BotPaddle* m_botPaddle;

        //Threads
        std::thread m_inputThread;
        std::thread m_ballCollisionsThread;
        

        
    public:
        Game(Ball* ball, Paddle* paddle, BotPaddle* botPaddle);
        virtual ~Game();

        void startGLoop();

        // Updating
        void update();
        void pollEvents();

        void getInput();

        //Rendering
        void render();
        void renderText(sf::RenderTarget& target);
        

        // Accessors
        const bool isRunning() const;

        
};

#endif
