//
// Created by gaspar_q on 3/9/16.
//

#include <algorithm>
#include <unistd.h>
#include <chrono>
#include "../include/Snake.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../include/Protocol.hpp"

const long Snake::snakeSpeed = 15;

const std::string                   Snake::bric2d = "./sprites/bric.bmp";
const std::string                   Snake::bricTxt = "#";
const GameComponent::Shapes         Snake::bric3d = GameComponent::CUBE_LARGE;
const AComponent::ComponentColor    Snake::bricColor = AComponent::COLOR_BLUE;
const std::string                   Snake::apple2d = "./sprites/apple.bmp";
const std::string                   Snake::appleTxt = " ";
const GameComponent::Shapes         Snake::apple3d = GameComponent::SPHERE_LARGE;
const AComponent::ComponentColor    Snake::appleColor = AComponent::COLOR_RED;
const std::string                   Snake::snkHd2d = "./sprites/snake_head.bmp";
const std::string                   Snake::snkHdTxt = " ";
const GameComponent::Shapes         Snake::snkHd3d = GameComponent::CUBE_LARGE;
const AComponent::ComponentColor    Snake::snkHdColor = AComponent::COLOR_GREEN;
const std::string                   Snake::snake2d = "./sprites/snake.bmp";
const std::string                   Snake::snakeTxt = " ";
const GameComponent::Shapes         Snake::snake3d = GameComponent::CUBE_LARGE;
const AComponent::ComponentColor    Snake::snakeColor = AComponent::COLOR_CYAN;

Snake::Snake() :
        AGame("Snake"),
        apple(NULL),
        score(0),
        snakeOri(UP),
        direction(0, 0),
        counter(0),
        uiScore(NULL),
        highScoreComponent(NULL),
        saved_keycode(-1)
{
    keycodex[ArcadeSystem::ArrowDown] = &Snake::goDown;
    keycodex[ArcadeSystem::ArrowLeft] = &Snake::goLeft;
    keycodex[ArcadeSystem::ArrowRight] = &Snake::goRight;
    keycodex[ArcadeSystem::ArrowUp] = &Snake::goUp;
    uiScore = new UIComponent(Vector2<double>(0, 0), AComponent::COLOR_WHITE, Vector2<double>(5, 1), "");
    basicStack.push(uiScore);
    for (size_t i = 0; i < ArcadeSystem::winWidth; ++i)
    {
        basicStack.push(new GameComponent(Vector2<double>(i, 0), Snake::bricColor, Snake::bric3d, Snake::bricTxt, Snake::bric2d));
        basicStack.push(new GameComponent(Vector2<double>(i, ArcadeSystem::winHeight - 1), Snake::bricColor, Snake::bric3d, Snake::bricTxt, Snake::bric2d));
    }
    for (size_t i = 1; i < ArcadeSystem::winHeight - 1; ++i)
    {
        basicStack.push(new GameComponent(Vector2<double>(0, i), Snake::bricColor, Snake::bric3d, Snake::bricTxt, Snake::bric2d));
        basicStack.push(new GameComponent(Vector2<double>(ArcadeSystem::winWidth - 1, i), Snake::bricColor, Snake::bric3d, Snake::bricTxt, Snake::bric2d));
    }
    for (size_t x = 1; x < ArcadeSystem::winWidth - 1; ++x)
    {
        for (size_t y = 1; y < ArcadeSystem::winHeight - 1; ++y)
        {
            plate.push_back(new GameComponent(Vector2<double>(x, y), Snake::bricColor, Snake::bric3d, Snake::bricTxt, Snake::bric2d));
        }
    }
    initGame();
}

Snake::~Snake()
{
    if (highScoreComponent)
        delete(highScoreComponent);
    for (std::list<GameComponent *>::iterator it = body.begin(), end = body.end(); it != end; ++it)
    {
        delete(*it);
    }
    for (std::list<GameComponent *>::iterator it = plate.begin(), end = plate.end(); it != end; ++it)
    {
        delete(*it);
    }
    while (!basicStack.empty())
    {
        delete (basicStack.top());
        basicStack.pop();
    }
}

std::stack<AComponent *>                    Snake::compute(int keycode)
{
    std::stack<AComponent *>                output;

    if (state == AGame::GameState::DEAD)
    {
        if (highScoreComponent)
            delete(highScoreComponent);
        highScoreComponent = new HighScoreComponent("Snake", score);
        highScoreComponent->UpdatePseudo(keycode);
        if (keycode == ArcadeSystem::Enter && highScoreComponent->submit())
        {
            state = AGame::GameState::ALIVE;
            delete(highScoreComponent);
            highScoreComponent = NULL;
            initGame();
        }
        else
            output.push(highScoreComponent);
    }
    else if (state == AGame::GameState::ALIVE)
    {
        output = basicStack;
        counter = counter + getMoveUnit(Snake::snakeSpeed);
        if (keycode != -1)
            saved_keycode = keycode;
        if (counter >= 1)
        {
            playARound();
            counter = 0;
        }
        uiScore->setText("score : " + std::to_string(score));
        uiScore->setPos(Vector2<double>(static_cast<int>(ArcadeSystem::winWidth - uiScore->getText().length()) / 2, 1));
        output.push(apple);
        for (std::list<GameComponent *>::iterator bod = body.begin(); bod != body.end(); ++bod)
        {
            output.push(*bod);
        }
    }
    return output;
}

void                                    Snake::playARound()
{
    std::map<int, keyfunc>::iterator    it;

    if ((it = keycodex.find(saved_keycode)) != keycodex.end())
        (this->*it->second)();
    saved_keycode = -1;
    goAhead();
}

void    Snake::restart()
{
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
    std::list<GameComponent *>::iterator it = plate.begin();

    if (plate.empty())
        return;
    index = random() % plate.size();
    for (size_t i = 0; i < index; ++i, ++it);
    apple = *it;
    apple->setSprite3D(Snake::apple3d);
    apple->setSprite2D(Snake::apple2d);
    apple->setSpriteText(Snake::appleTxt);
    apple->setColor(Snake::appleColor);
}

void Snake::removeBody()
{
    GameComponent *pos = body.back();

    body.pop_back();
    plate.push_back(pos);
}

void Snake::addBody(Vector2<double> newPos)
{
    GameComponent   *gameComponent = NULL;

    for (std::list<GameComponent *>::iterator it = plate.begin(), end = plate.end(); it != end; ++it)
    {
        if ((*it)->getPos() == newPos)
        {
            gameComponent = *it;
            break;
        }
    }
    if (gameComponent)
    {
        gameComponent->setSprite2D(Snake::snkHd2d);
        gameComponent->setSpriteText(Snake::snkHdTxt);
        gameComponent->setSprite3D(Snake::snkHd3d);
        gameComponent->setColor(Snake::snkHdColor);

        if (!body.empty())
        {
            body.front()->setSprite2D(Snake::snake2d);
            body.front()->setSpriteText(Snake::snakeTxt);
            body.front()->setSprite3D(Snake::snake3d);
            body.front()->setColor(Snake::snakeColor);
        }

        body.push_front(gameComponent);
        plate.remove(gameComponent);
    }
}

bool    Snake::goOnWall(Vector2<double> const &vector) const
{
    if (vector.x >= static_cast<int>(ArcadeSystem::winWidth) - 1 || vector.x <= 0)
    {
        return (true);
    }
    if (vector.y >= static_cast<int>(ArcadeSystem::winHeight) - 1 || vector.y <= 0)
    {
        return (true);
    }
    return (false);
}

void Snake::goAhead()
{
    Vector2<double> searchedPos(direction + body.front()->getPos());

    if (goOnWall(searchedPos))
        return die();
    for (std::list<GameComponent *>::iterator it = body.begin(), end = body.end(); it != end; ++it)
    {
      if ((*it)->getPos() == searchedPos)//direction)
	  {
	    return die();
	  }
    }
    move();
}

void Snake::move()
{
    addBody(direction + body.front()->getPos());
    if (body.front() == apple)
    {
        score += 10;
        generateAppelPos();
    }
    else
        removeBody();
}

double Snake::getMoveUnit(double unitPerSecond) const
{
    static std::chrono::high_resolution_clock::time_point   last_time = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point          curr_time;
    std::chrono::milliseconds                               time_diff;

    curr_time = std::chrono::high_resolution_clock::now();
    time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(curr_time - last_time);
    last_time = curr_time;
    return (unitPerSecond / 1000.0 * static_cast<double>(time_diff.count()));
}

void Snake::die()
{
//    initGame();
    state = AGame::GameState::DEAD;
}

void Snake::initGame()
{
    int midW = ArcadeSystem::winWidth / 2;
    int midH = ArcadeSystem::winHeight / 2;

    snakeOri = Snake::RIGHT;
    direction.x = 1;
    direction.y = 0;
    while (!body.empty())
    {
        plate.push_back(body.back());
        body.pop_back();
    }
    addBody(Vector2<double>(midW - 1, midH));
    addBody(Vector2<double>(midW, midH));
    addBody(Vector2<double>(midW + 1, midH));
    addBody(Vector2<double>(midW + 2, midH));
    generateAppelPos();
    score = 0;
}

GameComponent const *Snake::getApple() const
{
    return apple;
}

std::list<GameComponent *> const &Snake::getSnake() const
{
    return body;
}


extern "C" IGame *loadGame()
{
    return (new Snake());
}

void                                updateMap(struct arcade::GetMap *map, Snake const &snake)
{
    const GameComponent             *apple;
    std::list<GameComponent *>      snakeBody = snake.getSnake();

    //Reinit la map
    for (size_t i = 0, len = ArcadeSystem::winHeight * ArcadeSystem::winWidth; i < len; ++i)
    {
        map->tile[i] = arcade::TileType::EMPTY;
    }
    //Set appel pos
    apple = snake.getApple();
    map->tile[(int)apple->getPos().y * ArcadeSystem::winWidth + (int)apple->getPos().x] = arcade::TileType::POWERUP;
    //Set snake pos
    //    for (std::list<Vector2<double>>::iterator it = snakeBody.begin(), end = snakeBody.end(); it != end; ++it)
    //    {
    //        map->tile[(int)it->y * ArcadeSystem::winWidth + (int)it->x] = arcade::TileType::BLOCK;
    //    }
    //Set walls pos
    for (size_t i = 0; i < ArcadeSystem::winWidth; ++i)
    {
        map->tile[i] = arcade::TileType::BLOCK;
        map->tile[i + ArcadeSystem::winWidth * (ArcadeSystem::winHeight - 1)] = arcade::TileType::BLOCK;
    }
    for (size_t i = 1; i < ArcadeSystem::winHeight - 1; ++i)
    {
        map->tile[ArcadeSystem::winWidth * i] = arcade::TileType::BLOCK;
        map->tile[ArcadeSystem::winWidth * i + ArcadeSystem::winWidth - 1] = arcade::TileType::BLOCK;
    }
}

void                            whereAmI(Snake const &snake)
{
    struct arcade::WhereAmI     *pos;
    std::list<GameComponent *>  snakeBody = snake.getSnake();
    size_t                      posSize = sizeof(*pos) + snakeBody.size() * sizeof(arcade::Position);
    size_t                      i = 0;

    if ((pos = (struct arcade::WhereAmI *)malloc(posSize)) == NULL)
        throw std::bad_alloc();
    pos->type = arcade::CommandType::WHERE_AM_I;
    pos->lenght = static_cast<uint16_t>(snakeBody.size());
    for (std::list<GameComponent *>::iterator it = snakeBody.begin(), end = snakeBody.end(); it != end; ++it, ++i)
    {
        pos->position[i].x = static_cast<uint16_t>((*it)->getPos().x);
        pos->position[i].y = static_cast<uint16_t>((*it)->getPos().y);
    }
    write(1, pos, posSize);
    free(pos);
}

extern "C" void Play(void)
{
    char                        c;
    Snake                       snake;
    struct arcade::GetMap       *map;
    size_t                      mapSize = sizeof(*map) + ArcadeSystem::winWidth * ArcadeSystem::winHeight * sizeof(uint16_t);

    if ((map = (struct arcade::GetMap *)malloc(mapSize)) == NULL)
        throw std::bad_alloc();
    map->type = arcade::CommandType::GET_MAP;
    map->width = ArcadeSystem::winWidth;
    map->height = ArcadeSystem::winHeight;
    while (std::cin.read(&c, 1))
    {
        switch (static_cast<arcade::CommandType>(c))
        {
            case arcade::CommandType::WHERE_AM_I:
                whereAmI(snake);
                break;
            case arcade::CommandType::GET_MAP:
                updateMap(map, snake);
                write(1, map, mapSize);
                break;
            case arcade::CommandType::GO_UP:
                snake.goUp();
                break;
            case arcade::CommandType::GO_DOWN:
                snake.goDown();
                break;
            case arcade::CommandType::GO_LEFT:
                snake.goLeft();
                break;
            case arcade::CommandType::GO_RIGHT:
                snake.goRight();
                break;
            case arcade::CommandType::GO_FORWARD:
                snake.goAhead();
                break;
            case arcade::CommandType::PLAY:
                snake.playARound();
                break;
            default:
                break;
        }
    }
    free(map);
}
