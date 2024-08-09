#include "controller.h"

Controller::Controller(sf::Event &gameEvent, sf::Window &gameWindow, Model &gameModel, View &gameView){

    window = &gameWindow;
    event = &gameEvent;
    model = &gameModel;
    view = &gameView;
    pauseGame = false;

}

void Controller::pollEvents(){

    while(window->pollEvent(*event)){

        switch (event->type){

            case sf::Event::Closed:

                window->close();
                break;

            case sf::Event::KeyPressed:

                if (event->key.code == sf::Keyboard::Escape){

                    window->close();
                    break;

                }

                if (event->key.code == sf::Keyboard::Space){

                    view->TogglePause();
                    if (pauseGame){

                        pauseGame = false;

                    }
                    else{

                        pauseGame = true;

                    }
                    break;

                }

                if (!pauseGame){

                    if (event->key.code == sf::Keyboard::Right || event->key.code == sf::Keyboard::D){

                        if (model->GetDirection() != 'l'){

                            model->ChangeDirection('r');

                        }

                    }

                    if (event->key.code == sf::Keyboard::Left || event->key.code == sf::Keyboard::A){

                        if (model->GetDirection() != 'r'){

                            model->ChangeDirection('l');

                        }

                    }

                    if (event->key.code == sf::Keyboard::Down || event->key.code == sf::Keyboard::S){

                        if (model->GetDirection() != 'u'){

                            model->ChangeDirection('d');

                        }

                    }

                    if (event->key.code == sf::Keyboard::Up || event->key.code == sf::Keyboard::W){

                        if (model->GetDirection() != 'd'){

                            model->ChangeDirection('u');

                        }

                    }

                    break;

                }

                break;

        }

    }

}

bool Controller::getPauseState() const{

    return pauseGame;

}
