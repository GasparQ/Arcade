//
// CentipedeGame.hpp for GAME in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:17:37 2016 Victor Gouet
// Last update Fri Apr  1 16:24:08 2016 Victor Gouet
//

#ifndef CENTIPEDEGAME_HPP
# define CENTIPEDEGAME_HPP

#include <vector>
#include "AGame.hpp"
#include "USSEnterprise.hpp"
#include "Centipede.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/AudioComponent.hpp"


class CentipedeGame : public AGame
{
private:
    const char block = ' ' + 5;
    const int waveNbr = 10;

public:
    CentipedeGame();

    virtual ~CentipedeGame();

    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    std::vector<std::string> getMap() const;

    Centipede const &getCentipede() const;

    USSEnterprise const &getUssEntreprise() const;

    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void shoot();

private:
    void initMap();

    void displayMap(std::stack<AComponent *> &output) const;

    void onShoot(std::stack<AComponent *> &output);

    void initVariable();

    bool isEmptyCentipede() const;

private:
    Centipede centipede;
    USSEnterprise spaceShip;
    char map[31][51];
    int _score;
    int _wave;
    HighScoreComponent *highScoreComponent;
    std::stack<AComponent *> _oldStack;
    mutable std::stack<AComponent *> _output;
    UIComponent *waweCom;
    UIComponent *scoreCom;
    GameComponent *missilCom;
    AudioComponent *centipedeMusic;
};

#endif
