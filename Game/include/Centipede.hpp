//
// Centipede.hpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:28 2016 Victor Gouet
// Last update Sun Apr  3 15:49:57 2016 Victor Gouet
//

#ifndef CENTIPEDE_HPP_
# define CENTIPEDE_HPP_

# include "../../Commons/include/Vector2.hpp"
# include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/AudioComponent.hpp"
# include <map>
# include <list>
# include <vector>

class Centipede
{
public:
    Centipede(Vector2<double> const &);

    Centipede(Centipede const &);

    ~Centipede();

    Centipede &operator=(Centipede const &);

    typedef int (Centipede::*mptr)(char map[31][51], Vector2<double> &pos);

public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    static const double centipedeSpeed;

private:
    int goUp(char map[31][51], Vector2<double> &pos);

    int goDown(char map[31][51], Vector2<double> &pos);

    int goLeft(char map[31][51], Vector2<double> &pos);

    int goRight(char map[31][51], Vector2<double> &pos);

    class centipedeBody
    {
    public:
        centipedeBody(Vector2<double> const &pos, Direction direction) :
                pos(pos),
                direction(direction),
                gameComponent(new GameComponent(pos, AComponent::ComponentColor::COLOR_CYAN,
                                                GameComponent::Shapes::SPHERE_LARGE, " ", "FILE"))
        {
        }

        centipedeBody(centipedeBody const &ref) :
                pos(ref.pos),
                direction(ref.direction),
                gameComponent(new GameComponent(ref.pos, AComponent::ComponentColor::COLOR_CYAN,
                                                GameComponent::Shapes::SPHERE_LARGE, " ", "FILE"))
        {
        }

        void actualiseGameComponent() const
        {
            if (gameComponent)
            {
                gameComponent->setPos(this->pos);
                gameComponent->setSprite2D(direction == Direction::RIGHT ?  "./sprites/centipederight.bmp" : "./sprites/centipede.bmp");
            }
        }

        ~centipedeBody()
        {
            if (gameComponent)
                delete gameComponent;
        }

        bool operator==(centipedeBody const &ref)
        {
            return (pos == ref.pos && direction == ref.direction);
        }

        Vector2<double> pos;
        Direction direction;
        mutable GameComponent *gameComponent;
    };

private:
    Direction _dir;
    Direction _dir_prev;
    std::map<Direction, Vector2<double> > _directions;
    std::list<centipedeBody> _pos;
    Vector2<double> initPos;
    std::map<Direction, mptr> _map;
  AudioComponent	*centipedeMove;

public:
    int move(char map[31][51]);

    std::vector<AComponent *> getGameComponent() const;

    void add_node();

    bool isTouching(Vector2<double> const &vec) const;

    void splitCentipede(Vector2<double> const &pos);

    void clean();

public:
    std::list<Vector2<double> > getPos() const;
};

#endif
