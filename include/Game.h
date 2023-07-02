
#ifndef GAME_H
#define GAME_H
#pragma once

#include<iostream>
#include<thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Ball.h"
#include "Player1Paddle.h"
#include "Global.h"

class Game
{
    private:
        
        // Variables
        sf::RenderWindow* m_window;;
        sf::VideoMode m_videoMode;
        sf::Event m_event;


        int m_screenWidth;
        int m_screenHeight;

        sf::Clock m_paddleClock;
        sf::Clock m_ballClock;

        
        // Functions
        void initVariables();
        void initWindow();
        void initFont();
        void initText();

        // GUI
        sf::Font m_gameFont;
        sf::Text m_player1Text;
        sf::Text m_player2Text;

        // Objects
        Ball* m_ball;
        Player1Paddle* m_p1Paddle;
        

        
    public:
        Game(Ball& ball, Player1Paddle& p1Paddle);
        virtual ~Game();

        void startGLoop();

        // Updating
        void update();
        void pollEvents();
        void updateText();



        // Ball stuff (rock face)
        void updateBallCollisions();

        // Paddle shit
        void udpatePaddleCollisions();
        

        void getInput();

        //Rendering
        void render();
        void renderText(sf::RenderTarget& target);
        void renderBall(sf::RenderTarget& target);
        void renderPaddle(sf::RenderTarget& target);

        // Accessors
        const bool isRunning() const;

        
};

#endif
