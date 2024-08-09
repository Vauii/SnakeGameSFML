#pragma once
#include "model.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class View{

private:

    Model *model;
    sf::RenderWindow *window;

    float cellWidth;
    float cellHeight;

    sf::Color snakeColor;
    sf::Color appleColor;
    sf::Color backgroundColor;
    sf::Color pointsTextColor;
    sf::Color gameOverTextColor;
    sf::Color gamePausedTextColor;
    sf::Color snakeOutlineColor;

    sf::Font font;
    sf::Text pointsText;
    sf::Text gameOverText;
    sf::Text gamePausedText;

    std::deque<sf::RectangleShape> snakeCells;
    sf::RectangleShape apple;

    bool gamePaused;

    static constexpr const int OUTLINE_THICKNESS = 1;

    void InitVariables(Model &gameModel, sf::RenderWindow &renderWindow);
    void InitColors();
    void InitSnakeCells();
    void InitApple();
    void InitTexts();

public:

    View(Model &model, sf::RenderWindow &renderWindow);
    sf::Vector2f GetCellPosition(const int &row, const int &column) const;
    void UpdateSnake();
    void DrawSnake();
    void UpdateApple();
    void DrawApple();
    void UpdatePoints();
    void DrawPoints();
    void DrawGameOver();
    void DrawPause();
    void TogglePause();
    void Render();

};
