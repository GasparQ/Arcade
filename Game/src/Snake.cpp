//
// Created by gaspar_q on 3/9/16.
//

#include <algorithm>
#include "../include/Snake.hpp"
#include "../../Arcade.hpp"
#include "../../Component/include/GameComponent.hpp"

//TODO void play(void)

std::stack<AComponent *>                Snake::compute(int keycode)
{
    std::stack<AComponent *>            output;
    std::map<int, keyfunc>::iterator    it;
    std::list<Vector2>::iterator        bod;

    if ((it = keycodex.find(keycode)) != keycodex.end())
        (this->*it->second)();
    goAhead();
    for (bod = body.begin(); bod != body.end(); ++bod)
    {
      if (bod == body.begin())
	output.push(new GameComponent(*bod, AComponent::COLOR_GREEN, NULL, " ", "snake.bmp"));
      else
	output.push(new GameComponent(*bod, AComponent::COLOR_CYAN, NULL, " ", "snake.bmp"));
    }
    output.push(new GameComponent(apple, AComponent::COLOR_RED, NULL, " ", "appel.bmp"));
    return output;
}

void	Snake::restart()
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
    keycodex[arcade::ArrowDown] = &Snake::goDown;
    keycodex[arcade::ArrowLeft] = &Snake::goLeft;
    keycodex[arcade::ArrowRight] = &Snake::goRight;
    keycodex[arcade::ArrowUp] = &Snake::goUp;

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

bool	Snake::goOnWall(Vector2 const &vector) const
{
  if (vector.x >= static_cast<int>(arcade::winWidth) || vector.x < 0)
    {
      return (true);
    }
  if (vector.y >= static_cast<int>(arcade::winHeight) || vector.y < 0)
    {
      return (true);
    }
  return (false);
}

void Snake::goAhead()
{
    if (std::find<std::list<Vector2>::iterator, Vector2>(body.begin(), body.end(),
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
        generateAppelPos();
    else
        removeBody();
}

void Snake::die()
{
    initGame();
}

void Snake::initGame()
{
    int midW = arcade::winWidth / 2;
    int midH = arcade::winHeight / 2;

    plate.clear();
    body.clear();
    snakeOri = Snake::LEFT;
    direction.x = 1;
    direction.y = 0;
    for (size_t x = 0; x  < arcade::winWidth; ++x)
    {
        for (size_t y = 0; y < arcade::winHeight; ++y)
        {
            plate.push_back(Vector2(static_cast<int>(x), static_cast<int>(y)));
        }
    }
    addBody(Vector2(midW - 1, midH));
    addBody(Vector2(midW, midH));
    addBody(Vector2(midW + 1, midH));
    addBody(Vector2(midW + 2, midH));
    generateAppelPos();
    score = 0;
}

extern "C" IGame *loadGame()
{
  return (new Snake());
}
