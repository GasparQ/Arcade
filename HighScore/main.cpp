//
// main.cpp for Load in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 19:57:11 2016 Victor Gouet
// Last update Mon Mar 14 23:42:15 2016 Victor Gouet
//

#include "include/LoadHighScore.hpp"

int	main(int ac, char **av)
{
  if (ac != 5)
    {
      std::cerr << "./a.out [nbr] [string] [nbr] [string]" << std::endl;
      return (0);
    }

  try {
    LoadHighScore	load("snake");

    t_highScore		*score1 = new s_highScore(atoi(av[1]), av[2]);		
    load.setHighScore(score1);
    t_highScore		*score2 = new s_highScore(atoi(av[3]), av[4]);		
    load.setHighScore(score2);
    load.flush();
    std::cout << load << std::endl;
  }
  catch (std::exception const &e)
    {
      std::cout << e.what() << std::endl;
    }
}
