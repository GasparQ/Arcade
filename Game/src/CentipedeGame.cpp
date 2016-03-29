//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Tue Mar 29 14:27:53 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"

CentipedeGame::CentipedeGame() : AGame("Centipede")
{

}

CentipedeGame::~CentipedeGame()
{

}

std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
  std::stack<AComponent *>	output;

  

  return (output);
}

void CentipedeGame::restart()
{

}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}
