//
// HightScore.hpp for HightScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 17:40:43 2016 Victor Gouet
// Last update Mon Mar 14 23:01:41 2016 Victor Gouet
//

#ifndef HIGHTSCORE_HPP_
# define HIGHTSCORE_HPP_

# define MAGICNBR	1996

# include <cstring>
# include <iostream>

typedef struct	s_header
{
  int		magicNbr;
  int		headerSize;
  int		fileSize;
  int		nbrHightScore;

  s_header(int headerSize, int fileSize, int nbrHightScore)
    : magicNbr(MAGICNBR), headerSize(headerSize), fileSize(fileSize), nbrHightScore(nbrHightScore)
  {
  }

  s_header(){}
}		t_header;

typedef struct	s_hightScore
{
private:
  char		name[20];
  unsigned int	score;

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

  void		setScore(unsigned int newScore)
  {
    score = newScore;
  }

public:
  unsigned int	getScore() const
  {
    return (this->score);
  }

  std::string const getName() const
  {
    return (std::string(name));
  }

  s_hightScore(unsigned int newScore, std::string const &newName)
  {
    score = 0;
    std::memset(name, 0, sizeof(name));
    setName(newName);
    setScore(newScore);
  }

  s_hightScore()
  {
    score = 0;
    std::memset(name, 0, sizeof(name));
  }
}		t_hightScore;

#endif
