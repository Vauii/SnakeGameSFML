#include "view.h"

void View::InitVariables(Model &gameModel, sf::RenderWindow &renderWindow){

    model = &gameModel;
    window = &renderWindow;

    gamePaused = false;
    cellHeight = float(window->getSize().y) / float(model->rows);
    cellWidth = float(window->getSize().x) / float(model->columns);

}

void View::InitColors(){

    snakeColor = sf::Color(120, 24, 36);
    appleColor = sf::Color(30, 174, 36);
    pointsTextColor = sf::Color(20, 20, 20, 150);
    gameOverTextColor = sf::Color(170, 50, 50);
    backgroundColor = sf::Color(200, 200, 200);
    gamePausedTextColor = sf::Color(50, 50, 50);
    snakeOutlineColor = backgroundColor;

}

void View::InitSnakeCells(){

    for (auto & snakePart : model->snake){

        sf::RectangleShape tempRect;
        int row = snakePart[0];
        int column = snakePart[1];
        sf::Vector2f pos = GetCellPosition(row, column);

        tempRect.setSize(sf::Vector2f(cellWidth, cellHeight));
        tempRect.setFillColor(snakeColor);
        tempRect.setOutlineThickness(OUTLINE_THICKNESS);
        tempRect.setOutlineColor(snakeOutlineColor);
        tempRect.setPosition(pos);

        snakeCells.push_back(tempRect);

    }

}

void View::InitApple() {

    apple.setSize(sf::Vector2f(cellWidth, cellHeight));
    apple.setFillColor(appleColor);
    sf::Vector2f applePos = GetCellPosition(model->appleY, model->appleX);
    apple.setPosition(applePos);

}

void View::InitTexts(){

    font.loadFromFile("C:/Users/Public/clion_coding/lab_6/arial.ttf");

    pointsText.setFont(font);
    pointsText.setFillColor(pointsTextColor);
    pointsText.setStyle(sf::Text::Bold);
    pointsText.setPosition(20, 20);
    pointsText.setString("POINTS: " + std::to_string(model->points));

    gameOverText.setFont(font);
    gameOverText.setFillColor(gameOverTextColor);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setCharacterSize(100);
    gameOverText.setString("GAME OVER");
    sf::FloatRect gameOverRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverRect.left + gameOverRect.width / 2.0f,
                           gameOverRect.top + gameOverRect.height / 2.0f);
    gameOverText.setPosition(float(window->getSize().x) / 2.0f, float(window->getSize().y) / 2.0f);


    gamePausedText.setFont(font);
    gamePausedText.setFillColor(gamePausedTextColor);
    gamePausedText.setStyle(sf::Text::Bold);
    gamePausedText.setCharacterSize(100);
    gamePausedText.setString("GAME PAUSED");
    sf::FloatRect gamePausedRect = gamePausedText.getLocalBounds();
    gamePausedText.setOrigin(gamePausedRect.left + gamePausedRect.width / 2.0f,
                             gamePausedRect.top + gamePausedRect.height / 2.0f);
    gamePausedText.setPosition(float(window->getSize().x) / 2.0f, float(window->getSize().y) / 2.0f);

}

View::View(Model &gameModel, sf::RenderWindow &renderWindow){


    InitVariables(gameModel, renderWindow);
    InitColors();
    InitSnakeCells();
    InitApple();
    InitTexts();

}

sf::Vector2f View::GetCellPosition(const int &row, const int &column) const{

    float y = cellHeight * float(row);
    float x = cellWidth * float(column);

    return sf::Vector2f{x, y};

}

void View::UpdateSnake(){

    if (model->snake.size() == snakeCells.size()){

        snakeCells.pop_back();

    }

    sf::RectangleShape newHead;
    int row = model->snake.front()[0];
    int column = model->snake.front()[1];
    sf::Vector2f pos = GetCellPosition(row, column);
    pos.x += OUTLINE_THICKNESS;
    pos.y += OUTLINE_THICKNESS;

    newHead.setSize(sf::Vector2f(cellWidth - OUTLINE_THICKNESS * 2, cellHeight - OUTLINE_THICKNESS * 2));
    newHead.setFillColor(snakeColor);
    newHead.setOutlineThickness(OUTLINE_THICKNESS);
    newHead.setOutlineColor(snakeOutlineColor);
    newHead.setPosition(pos);

    snakeCells.push_front(newHead);

}

void View::DrawSnake(){

    for (const auto& snakeCell: snakeCells){

        (*window).draw(snakeCell);

    }

}

void View::UpdateApple(){

    sf::Vector2f applePos = GetCellPosition(model->appleY, model->appleX);
    apple.setPosition(applePos);

}

void View::DrawApple(){

    (*window).draw(apple);

}

void View::UpdatePoints(){

    pointsText.setString("POINTS: " + std::to_string(model->points));

}


void View::DrawPoints(){

    (*window).draw(pointsText);

}

void View::Render(){

    window->clear(backgroundColor);

    if (!model->GetSnakeCollision() && !gamePaused){

        (*this).UpdateSnake();
        (*this).UpdateApple();
        (*this).UpdatePoints();

    }


    (*this).DrawSnake();
    (*this).DrawApple();
    (*this).DrawPoints();
    if (gamePaused && !model->GetSnakeCollision()){

        (*this).DrawPause();

    }
    if (model->GetSnakeCollision()){

        (*this).DrawGameOver();

    }
    window->display();

}

void View::DrawGameOver() {

    window->draw(gameOverText);

}

void View::DrawPause(){

    window->draw(gamePausedText);

}

void View::TogglePause(){

    if (gamePaused){

        gamePaused = false;

    }
    else{

        gamePaused = true;

    }

}


