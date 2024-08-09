#pragma once
#include "model.h"
#include "view.h"
#include "SFML/Graphics.hpp"

class Controller {

private:

    sf::Event *event;
    sf::Window *window;
    View *view;
    Model *model;

    bool pauseGame;

public:

    Controller(sf::Event &gameEvent, sf::Window &gameWindow, Model &gameModel, View &gameView);

    void pollEvents();
    bool getPauseState() const;

};
