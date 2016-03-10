//
// Created by gaspar_q on 3/9/16.
//

#include <algorithm>
#include "../include/Snake.hpp"
#include "../../Arcade.hpp"
#include "../../Component/include/GameComponent.hpp"

std::stack<AComponent *>                Snake::compute(int keycode)
{
    std::stack<AComponent *>            output;
    std::map<int, keyfunc>::iterator    it;
    std::list<Vector2>::iterator        bod;

    if ((it = keycodex.find(keycode)) != keycodex.end())
        (this->*it->second)();
    addBody(body.front() + direction);
    removeBody();
    if (body.front() == apple)
    {
        body.push_back(apple);
        plate.remove(apple);
        generateAppelPos();
    }
    for (bod = body.begin(); bod != body.end(); ++bod)
    {
        output.push(new GameComponent(*bod, NULL, " ", "snake.bmp"));
    }
    output.push(new GameComponent(apple, NULL, "ð", "appel.bmp"));
    return output;
}

Snake::~Snake()
{

}

Snake::Snake() :
    apple(0, 0),
    score(0),
    snakeOri(Snake::LEFT),
    direction(1, 0)
{
    int midW = arcade::winWidth / 2;
    int midH = arcade::winHeight / 2;

    keycodex[arcade::ArrowDown] = &Snake::goDown;
    keycodex[arcade::ArrowLeft] = &Snake::goLeft;
    keycodex[arcade::ArrowRight] = &Snake::goRight;
    keycodex[arcade::ArrowUp] = &Snake::goUp;

    for (size_t i = 0, end = arcade::winWidth * arcade::winHeight; i  < end; ++i)
    {
        plate.push_back(Vector2(static_cast<int>(i % arcade::winWidth), static_cast<int>(i / arcade::winHeight)));
    }
    addBody(Vector2(midW + 2, midH));
    addBody(Vector2(midW + 1, midH));
    addBody(Vector2(midW, midH));
    addBody(Vector2(midW - 1, midH));
}

void Snake::goUp()
{
    if (snakeOri == DOWN || snakeOri == UP)
        return;
    snakeOri = UP;
    direction.y = 1;
    direction.x = 0;
}

void Snake::goDown()
{
    if (snakeOri == DOWN || snakeOri == UP)
        return;
    snakeOri = DOWN;
    direction.y = -1;
    direction.x = 0;
}

void Snake::goLeft()
{
    if (snakeOri == LEFT || snakeOri == RIGHT)
        return;
    snakeOri = LEFT;
    direction.y = 0;
    direction.x = 1;
}

void Snake::goRight()
{
    if (snakeOri == LEFT || snakeOri == RIGHT)
        return;
    snakeOri = RIGHT;
    direction.y = 0;
    direction.x = -1;
}

void                                Snake::generateAppelPos()
{
    size_t                          index;
    std::list<Vector2>::iterator    it = plate.begin();

    if (plate.empty())
        return;
    index = random() % plate.size();
    for (size_t i = 0; i < index; ++i, ++it);
    apple = *it;
    plate.erase(it);
}

void Snake::removeBody()
{
    Vector2 pos = body.back();

    body.pop_back();
    plate.push_back(pos);
}

void Snake::addBody(Vector2 newPos)
{
    body.push_front(newPos);
    plate.remove(newPos);
}
