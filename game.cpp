#include "game.h"

Game::Game(){

    videoMode.width = WINDOW_WIDTH;
    videoMode.height = WINDOW_HEIGHT;

    window = new sf::RenderWindow(videoMode, "My Snake Game", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(15);

    model = new Model();
    view = new View(*model, *window);
    controller = new Controller(event, *window, *model, *view);

    endGame = false;

}

Game::~Game(){

    delete controller;
    delete view;
    delete model;
    delete window;

}

void Game::Render(){

    view->Render();

}

void Game::Update(){

    controller->pollEvents();
    if (controller->getPauseState()){

        return;

    }
    model->Move();
    model->ProcessCollisions();
    endGame = model->GetSnakeCollision();

}

bool Game::IsRunning() const{

    return window->isOpen();

}

bool Game::GetEndGame() const{

    return endGame;

}

void Game::Run(){


    while((*this).IsRunning()){

        while(!(*this).GetEndGame() && (*this).IsRunning()){

            (*this).Update();
            (*this).Render();

        }

        controller->pollEvents();
        (*this).Render();

    }

}

