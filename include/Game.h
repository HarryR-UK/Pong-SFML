
#ifndef GAME_H
#define GAME_H
#pragma once

#include<iostream>
#include<thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Game
{
    private:
        
        // Variables
        sf::RenderWindow* m_window;;
        sf::VideoMode m_videoMode;
        sf::Event m_event;


        int m_screenWidth;
        int m_screenHeight;

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
        

        
    public:
        Game();
        virtual ~Game();

        void startGLoop();

        // Updating
        void update();
        void pollEvents();
        void updateText();




        

        void getInput();

        //Rendering
        void render();
        void renderText(sf::RenderTarget& target);

        // Accessors
        const bool isRunning() const;

        
};

#endif
