#pragma once
#include "controller.h"
#include "view.h"
#include "model.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game {

private:

    sf::Event event{};
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    Model *model;
    View *view;
    Controller *controller;

    bool endGame;

    constexpr static const int WINDOW_WIDTH = 800;
    constexpr static const int WINDOW_HEIGHT = 600;

public:

    Game();
    ~Game();
    void Update();
    void Render();
    void Run();
    bool GetEndGame() const;
    bool IsRunning() const;

};
