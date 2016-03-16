//
// Created by gaspar_q on 3/9/16.
//

#include <algorithm>
#include <unistd.h>
#include "../include/Snake.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../include/Protocol.hpp"

//TODO void play(void)

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

Snake::~Snake()
{

}

std::stack<AComponent *>                Snake::compute(int keycode)
{
    std::stack<AComponent *>            output;
    std::map<int, keyfunc>::iterator    it;
    std::list<Vector2<int> >::iterator  bod;
    HighScoreComponent                  *highScoreComponent;

    if (state == AGame::GameState::DEAD)
    {
        highScoreComponent = new HighScoreComponent("Snake", score);
        highScoreComponent->UpdatePseudo(keycode);
        if (keycode == ArcadeSystem::Enter && highScoreComponent->submit())
        {
            state = AGame::GameState::ALIVE;
            delete(highScoreComponent);
            initGame();
        }
        else
            output.push(highScoreComponent);
    }
    else if (state == AGame::GameState::ALIVE)
    {
        if ((it = keycodex.find(keycode)) != keycodex.end())
            (this->*it->second)();
        goAhead();
        output.push(new UIComponent(Vector2<int>((static_cast<int>(ArcadeSystem::winWidth - std::string("score : " + std::to_string(score)).size()) / 2), 1),
                                    AComponent::COLOR_WHITE,
                                    Vector2<int>(5, 1), "score : " + std::to_string(score)));
    }
    for (bod = body.begin(); bod != body.end(); ++bod)
    {
        if (bod == body.begin())
            output.push(new GameComponent(*bod, AComponent::COLOR_GREEN, GameComponent::Shapes::CUBE , " ", "./sprites/snake_head.bmp"));
        else
            output.push(new GameComponent(*bod, AComponent::COLOR_CYAN, GameComponent::Shapes::CUBE , " ", "./sprites/snake.bmp"));
    }
    output.push(new GameComponent(apple, AComponent::COLOR_RED, GameComponent::Shapes::SPHERE_LARGE, " ", "./sprites/apple.bmp"));
    return output;
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
//    initGame();
    state = AGame::GameState::DEAD;
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

const Vector2<int> &Snake::getApple() const
{
    return apple;
}

std::list<Vector2<int>> const &Snake::getSnake() const
{
    return body;
}


extern "C" IGame *loadGame()
{
    return (new Snake());
}

void                            updateMap(struct arcade::GetMap *map, Snake const &snake)
{
    Vector2<int>                apple(0, 0);
    std::list<Vector2<int>>     snakeBody = snake.getSnake();

    //Reinit la map
    for (size_t i = 0, len = ArcadeSystem::winHeight * ArcadeSystem::winWidth; i < len; ++i)
    {
        map->tile[i] = arcade::TileType::EMPTY;
    }
    //Set appel pos
    apple = snake.getApple();
    map->tile[apple.y * ArcadeSystem::winWidth + apple.x] = arcade::TileType::POWERUP;
    //Set snake pos
    for (std::list<Vector2<int>>::iterator it = snakeBody.begin(), end = snakeBody.end(); it != end; ++it)
    {
        map->tile[it->y * ArcadeSystem::winWidth + it->x] = arcade::TileType::BLOCK;
    }
}

void    whereAmI(Snake const &snake)
{
    struct arcade::WhereAmI *pos;
    std::list<Vector2<int>> snakeBody = snake.getSnake();
    size_t                  posSize = sizeof(*pos) + snakeBody.size() * sizeof(arcade::Position);
    size_t                  i = 0;

    if ((pos = (struct arcade::WhereAmI *)(malloc(posSize))) == NULL)
        throw std::bad_alloc();
    pos->type = arcade::CommandType::WHERE_AM_I;
    pos->lenght = static_cast<uint16_t>(snakeBody.size());
    for (std::list<Vector2<int>>::iterator it = snakeBody.begin(), end = snakeBody.end(); it != end; ++it, ++i)
    {
        pos->position[i].x = static_cast<uint16_t>(it->x);
        pos->position[i].y = static_cast<uint16_t>(it->y);
    }
    write(1, pos, posSize);
    free(pos);
}

extern "C" void Play(void)
{
    char                    c;
    Snake                   snake;
    struct arcade::GetMap   *map;
    size_t                  mapSize = sizeof(*map) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight * sizeof(uint16_t));

    if ((map = (struct arcade::GetMap   *)(malloc(mapSize))) == NULL)
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
                snake.compute(-1);
                break;
            default:
                break;
        }
    }
    free(map);
}