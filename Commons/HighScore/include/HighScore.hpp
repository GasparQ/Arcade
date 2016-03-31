//
// HighScore.hpp for HighScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HighScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 17:40:43 2016 Victor Gouet
// Last update Thu Mar 31 23:19:25 2016 Victor Gouet
//

#ifndef HIGHSCORE_HPP_
# define HIGHSCORE_HPP_

# define MAGICNBR	1996

# include <cstring>
# include <iostream>

typedef struct	s_header
{
  int		magicNbr;
  int		headerSize;
  int		fileSize;
  int		nbrHighScore;

  s_header(int headerSize, int fileSize, int nbrHighScore)
    : magicNbr(MAGICNBR), headerSize(headerSize), fileSize(fileSize), nbrHighScore(nbrHighScore)
  {
  }

  s_header(){}
}		t_header;

typedef struct	s_highScore
{
private:
  char		name[20];
  int		score;

  void	        setName(std::string const &newName)
  {
    unsigned int	i = 0;

    while (i < newName.size() && i < sizeof(name) - 1)
      {
	name[i] = newName[i];
	++i;
      }
    name[i] = '\0';
  }

  void		setScore(int newScore)
  {
    score = newScore;
  }

public:
  int		getScore() const
  {
    return (this->score);
  }

  std::string const getName() const
  {
    return (std::string(name));
  }

  s_highScore(int newScore, std::string const &newName)
  {
    score = 0;
    std::memset(name, 0, sizeof(name));
    setName(newName);
    setScore(newScore);
  }

  s_highScore()
  {
    score = 0;
    std::memset(name, 0, sizeof(name));
  }
}		t_highScore;

#endif
