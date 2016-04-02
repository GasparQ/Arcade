//
// Created by gaspar_q on 3/9/16.
//

#ifndef C_SNAKE_HPP
#define C_SNAKE_HPP

#include <stack>
#include <list>
#include <map>
#include <string>

#include "../../Commons/include/AComponent.hpp"
#include "../../Graphique/include/IGraph.hpp"
#include "AGame.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../../Commons/AudioComponent.hpp"

class Snake : public AGame
{
public:
    static const std::string                    bric2d;
    static const std::string                    bricTxt;
    static const GameComponent::Shapes          bric3d;
    static const AComponent::ComponentColor     bricColor;
    static const std::string                    apple2d;
    static const std::string                    appleTxt;
    static const GameComponent::Shapes          apple3d;
    static const AComponent::ComponentColor     appleColor;
    static const std::string                    snkHd2d;
    static const std::string                    snkHdTxt;
    static const GameComponent::Shapes          snkHd3d;
    static const AComponent::ComponentColor     snkHdColor;
    static const std::string                    snake2d;
    static const std::string                    snakeTxt;
    static const GameComponent::Shapes          snake3d;
    static const AComponent::ComponentColor     snakeColor;

public:
    Snake();

    virtual ~Snake();

public:
    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    void playARound();

    typedef void (Snake::*keyfunc)();

    static const long snakeSpeed;

private:
    typedef enum
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } Orientation;

private:
    std::list<GameComponent *>  body;
    GameComponent               *apple;
    size_t                      score;
    Orientation                 snakeOri;
    Vector2<double>             direction;
    double                      counter;
    UIComponent                 *uiScore;
    HighScoreComponent          *highScoreComponent;
    int                         saved_keycode;
    std::map<int, keyfunc>      keycodex;
    std::list<GameComponent *>  plate;
    std::stack<AComponent *>    basicStack;
    std::stack<AComponent *>                output;
    AudioComponent m_gameMusic;

public:
    void goUp();

    void goDown();

    void goLeft();

    void goRight();

    void goAhead();

    GameComponent const *getApple() const;

    std::list<GameComponent *> const &getSnake() const;

    double getMoveUnit(double unitPerSecond) const;

private:
    void generateAppelPos();

    void removeBody();

    void addBody(Vector2<double> newPos);

    void move();

    void die();

    void initGame();

    bool goOnWall(Vector2<double> const &vector) const;
};

#endif //C_SNAKE_HPP
