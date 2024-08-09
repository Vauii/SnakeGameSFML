#include "model.h"


Model::Model(): rows(DEFAULT_ROWS), columns(DEFAULT_COLUMNS){

    field = new int*[rows];
    for (int i = 0; i < rows; i++){

        field[i] = new int[columns];
        std::fill(field[i], field[i] + columns, 0);

    }

    int middleY = rows/2, middleX = columns/2;

    for (int i = 0; i <= SNAKE_INITIAL_LENGTH; i++){

        field[middleY][middleX - i] = ID_SNAKE;
        snake.push_back(std::vector<int>{middleY, middleX - i});

    }

    points = 0;
    appleIsEaten = false;
    direction = 'r';

    generator = std::mt19937{static_cast<std::mt19937::result_type>(std::time(nullptr))};

    (*this).SpawnApple();

}

Model::~Model(){

    for (int i = 0; i < rows; i++){

        delete field[i];

    }

    delete field;

}

void Model::CutTail(){

    if (!appleIsEaten){

        field[snake.back()[0]][snake.back()[1]] = 0;
        snake.pop_back();
        return;

    }
    appleIsEaten = false;

}

void Model::MoveRight(){

    (*this).CutTail();

    if (snake.front()[1] + 1 == columns){

        snake.push_front(std::vector<int>{snake.front()[0], 0});

    }
    else{

        snake.push_front(std::vector<int>{snake.front()[0], snake.front()[1] + 1});

    }

}

void Model::MoveLeft(){

    (*this).CutTail();

    if (snake.front()[1] - 1 == -1){

        snake.push_front(std::vector<int>{snake.front()[0], columns - 1});

    }
    else{

        snake.push_front(std::vector<int>{snake.front()[0], snake.front()[1] - 1});

    }

}

void Model::MoveUp(){

    (*this).CutTail();

    if (snake.front()[0] - 1 == -1){

        snake.push_front(std::vector<int>{rows - 1, snake.front()[1]});

    }
    else{

        snake.push_front(std::vector<int>{snake.front()[0] - 1, snake.front()[1]});

    }

}

void Model::MoveDown(){

    (*this).CutTail();

    if (snake.front()[0] + 1 == rows){

        snake.push_front(std::vector<int>{0, snake.front()[1]});

    }
    else{

        snake.push_front(std::vector<int>{snake.front()[0] + 1, snake.front()[1]});

    }

}

void Model::SpawnApple(){

    std::uniform_int_distribution<int> randomY{0, rows - 1};
    std::uniform_int_distribution<int> randomX{0, columns - 1};

    do{

        appleX = randomX(generator);
        appleY = randomY(generator);


    } while (field[appleY][appleX] != 0);

    field[appleY][appleX] = ID_APPLE;


}


void Model::Move(){

    switch (direction){

        case 'r':

            (*this).MoveRight();
            return;

        case 'u':

            (*this).MoveUp();
            return;

        case 'l':

            (*this).MoveLeft();
            return;

        case 'd':

            (*this).MoveDown();
            return;

    }

}


void Model::ProcessCollisions(){

    int headCellId = field[snake.front()[0]][snake.front()[1]];

    switch (headCellId){

        case ID_SNAKE:

            snakeCollision = true;
            return;

        case ID_APPLE:

            field[snake.front()[0]][snake.front()[1]] = ID_SNAKE;
            appleIsEaten = true;
            points += POINTS_APPLE;
            (*this).SpawnApple();
            snakeCollision = false;
            return;

        default:

            field[snake.front()[0]][snake.front()[1]] = ID_SNAKE;
            snakeCollision = false;
            return;

    }

}

void Model::ChangeDirection(const char &newDirection){

    direction = newDirection;

}

bool Model::GetSnakeCollision() const{

    return snakeCollision;

}

char Model::GetDirection() const {

    return direction;

}

