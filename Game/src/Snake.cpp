//
// Created by gaspar_q on 3/9/16.
//

#include <algorithm>
#include "../include/Snake.hpp"
#include "../../Component/include/GameComponent.hpp"
#include "../../Component/include/UIComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

//TODO void play(void)

std::stack<AComponent *>                Snake::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::map<int, keyfunc>::iterator it;
    std::list<Vector2<int> >::iterator bod;

    if ((it = keycodex.find(keycode)) != keycodex.end())
        (this->*it->second)();
    goAhead();
    for (bod = body.begin(); bod != body.end(); ++bod)
    {
        if (bod == body.begin())
            output.push(new GameComponent(*bod, AComponent::COLOR_GREEN, NULL, " ", "./sprites/snake_head.bmp"));
        else
            output.push(new GameComponent(*bod, AComponent::COLOR_CYAN, NULL, " ", "./sprites/snake.bmp"));
    }
    output.push(new GameComponent(apple, AComponent::COLOR_RED, NULL, " ", "./sprites/apple.bmp"));

    output.push(new UIComponent(
            Vector2<int>((static_cast<int>(ArcadeSystem::winWidth - std::string("score : " + std::to_string(score)).size()) / 2), 1),
            AComponent::COLOR_WHITE,
            Vector2<int>(0, 0), "score : " + std::to_string(score))
    );
    return output;
}

void    Snake::restart()
{
    initGame();
}

Snake::~Snake()
{

}

Snake::Snake() :
        apple(0, 0),
        score(0),
        snakeOri(UP),
        direction(0, 0)
{
    keycodex[ArcadeSystem::ArrowDown] = &Snake::goDown;
    keycodex[ArcadeSystem::ArrowLeft] = &Snake::goLeft;
    keycodex[ArcadeSystem::ArrowRight] = &Snake::goRight;
    keycodex[ArcadeSystem::ArrowUp] = &Snake::goUp;

    initGame();
}

void Snake::goUp()
{
    if (snakeOri == DOWN || snakeOri == UP)
        return;
    snakeOri = UP;
    direction.y = -1;
    direction.x = 0;
}

void Snake::goDown()
{
    if (snakeOri == DOWN || snakeOri == UP)
        return;
    snakeOri = DOWN;
    direction.y = 1;
    direction.x = 0;
}

void Snake::goLeft()
{
    if (snakeOri == LEFT || snakeOri == RIGHT)
        return;
    snakeOri = LEFT;
    direction.y = 0;
    direction.x = -1;
}

void Snake::goRight()
{
    if (snakeOri == LEFT || snakeOri == RIGHT)
        return;
    snakeOri = RIGHT;
    direction.y = 0;
    direction.x = 1;
}

void                                Snake::generateAppelPos()
{
    size_t index;
    std::list<Vector2<int> >::iterator it = plate.begin();

    if (plate.empty())
        return;
    index = random() % plate.size();
    for (size_t i = 0; i < index; ++i, ++it);
    apple = *it;
    plate.erase(it);
}

void Snake::removeBody()
{
    Vector2<int> pos = body.back();

    body.pop_back();
    plate.push_back(pos);
}

void Snake::addBody(Vector2<int> newPos)
{
    body.push_front(newPos);
    plate.remove(newPos);
}

bool    Snake::goOnWall(Vector2<int> const &vector) const
{
    if (vector.x >= static_cast<int>(ArcadeSystem::winWidth) || vector.x < 0)
    {
        return (true);
    }
    if (vector.y >= static_cast<int>(ArcadeSystem::winHeight) || vector.y < 0)
    {
        return (true);
    }
    return (false);
}

void Snake::goAhead()
{
    if (std::find<std::list<Vector2<int> >::iterator, Vector2<int> >(body.begin(), body.end(),
                                                         body.front() + direction) != body.end()
        || goOnWall(body.front() + direction))
        die();
    else
        move();
}

void Snake::move()
{
    addBody(body.front() + direction);
    if (body.front() == apple)
    {
        score += 10;
        generateAppelPos();
    }
    else
        removeBody();
}

void Snake::die()
{
    initGame();
}

void Snake::initGame()
{
    int midW = ArcadeSystem::winWidth / 2;
    int midH = ArcadeSystem::winHeight / 2;

    plate.clear();
    body.clear();
    snakeOri = Snake::RIGHT;
    direction.x = 1;
    direction.y = 0;
    for (size_t x = 0; x < ArcadeSystem::winWidth; ++x)
    {
        for (size_t y = 0; y < ArcadeSystem::winHeight; ++y)
        {
            plate.push_back(Vector2<int>(static_cast<int>(x), static_cast<int>(y)));
        }
    }
    addBody(Vector2<int>(midW - 1, midH));
    addBody(Vector2<int>(midW, midH));
    addBody(Vector2<int>(midW + 1, midH));
    addBody(Vector2<int>(midW + 2, midH));
    generateAppelPos();
    score = 0;
}

extern "C" IGame *loadGame()
{
    return (new Snake());
}
