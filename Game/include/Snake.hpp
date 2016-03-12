//
// Created by gaspar_q on 3/9/16.
//

#ifndef C_SNAKE_HPP
#define C_SNAKE_HPP

#include <stack>
#include <list>
#include <map>
#include <string>

#include "../../Component/include/AComponent.hpp"
#include "../../Graphique/include/IGraph.hpp"
#include "IGame.hpp"
#include "../../Vector/include/Vector2.hpp"

class Snake : public IGame
{
public:
    Snake();
    virtual ~Snake();

public:
  virtual std::stack<AComponent *> compute(int keycode);
  virtual void	restart();

  typedef void (Snake::*keyfunc)();

private:
    typedef enum
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } Orientation;

private:
    std::list<Vector2>          body;
    Vector2                     apple;
    size_t                      score;
    Orientation                 snakeOri;
    Vector2                     direction;
    std::map<int, keyfunc>      keycodex;
    std::list<Vector2>          plate;

public:
    void                        goUp();
    void                        goDown();
    void                        goLeft();
    void                        goRight();
    void                        goAhead();

private:
    void                        generateAppelPos();
    void                        removeBody();
    void                        addBody(Vector2 newPos);
    void                        move();
    void                        die();
    void                        initGame();
  bool goOnWall(Vector2 const &vector) const;
};

#endif //C_SNAKE_HPP
