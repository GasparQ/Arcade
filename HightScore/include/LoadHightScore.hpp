//
// LoadHightScore.hpp for LoadHightScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 17:51:22 2016 Victor Gouet
// Last update Mon Mar 14 23:29:53 2016 Victor Gouet
//

#ifndef LOADHIGHTSCORE_HPP_
# define LOADHIGHTSCORE_HPP_

# include <algorithm>
# include <iostream>
# include <vector>
# include "HightScore.hpp"
# include <fstream>
# include <fstream>
# include <sstream>
# include <sys/mman.h>
# include <stdexcept>

class	LoadHightScore
{
public:
  LoadHightScore(std::string const &fileName);
  ~LoadHightScore();

public:
  void					setHightScore(t_hightScore const *newScore);
  const std::vector<t_hightScore const *>	getAllHightScore() const;
  std::string const			&getFileName() const;
  void					flush() const;

private:
  static bool					isUpper(const t_hightScore *, const t_hightScore *);

private:
  const std::string			fileName;
  std::vector<t_hightScore const *>	hightScoreList;
};

std::ostream &operator<<(std::ostream &ostream, LoadHightScore const &hightScore);

#endif
