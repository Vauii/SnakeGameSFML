#pragma once
#include <vector>
#include <deque>
#include <random>
#include <ctime>

class Model {

    friend class View;

private:

    int **field;
    const int rows;
    const int columns;
    std::deque<std::vector<int>> snake;
    int appleX{};
    int appleY{};
    int points;
    bool appleIsEaten;
    bool snakeCollision;
    char direction;
    std::mt19937 generator;

    constexpr static const int DEFAULT_ROWS = 30;
    constexpr static const int DEFAULT_COLUMNS = 40;
    constexpr static const int POINTS_APPLE = 50;
    constexpr static const int SNAKE_INITIAL_LENGTH = 4;
    constexpr static const int ID_SNAKE = 1;
    constexpr static const int ID_APPLE = 2;

public:

    Model();
    ~Model();

    void ProcessCollisions();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    void Move();
    void ChangeDirection(const char &newDirection);
    void SpawnApple();
    void CutTail();
    bool GetSnakeCollision() const;
    char GetDirection() const;

};
