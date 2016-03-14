//
// LoadHightScore.cpp for LoadHightScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 18:04:40 2016 Victor Gouet
// Last update Mon Mar 14 23:31:34 2016 Victor Gouet
//

#include "../include/LoadHightScore.hpp"

LoadHightScore::LoadHightScore(std::string const &fileName) : fileName(fileName)
{
  std::ifstream		fd;
  std::stringstream	buffer;
  t_header		header;
  int			lenght;
  int			i;

  fd.open(fileName.c_str(), std::ios::in | std::fstream::binary);
  if (fd.is_open())
    {
      fd.seekg(0, fd.end);
      lenght = fd.tellg();
      fd.seekg(0, fd.beg);
      fd.read(reinterpret_cast<char *>(&header), sizeof(t_header));
      if (header.magicNbr != MAGICNBR)
	throw std::out_of_range("LoadHightScore: Bad Magic Number");
      if (header.headerSize != sizeof(t_header))
	throw std::out_of_range("LoadHightScore: Bad header size");
      if (header.fileSize != lenght)
      	throw std::out_of_range("LoadHightScore: Bad file size");
      i = 0;
      while (i < header.nbrHightScore
	     && (int)(sizeof(t_header) + (sizeof(t_hightScore) * i)) < header.fileSize)
	{
	  t_hightScore	*hightScore = new s_hightScore();
	  fd.read(reinterpret_cast<char *>(hightScore), sizeof(t_hightScore));
	  hightScoreList.push_back(hightScore);
	  ++i;
	}
      fd.close();
    }
}

LoadHightScore::~LoadHightScore()
{
  std::vector<t_hightScore const *>::const_iterator	it = hightScoreList.begin();

  while (it != hightScoreList.end())
    {
      delete *it;
      ++it;
    }
}

bool		     LoadHightScore::isUpper(const t_hightScore *first,
					     const t_hightScore *last)
{
  return (first->getScore() > last->getScore());
}

void					LoadHightScore::setHightScore(t_hightScore const *newScore)
{
  hightScoreList.push_back(newScore);
  std::sort(hightScoreList.begin(), hightScoreList.end(), LoadHightScore::isUpper);
}

const std::vector<t_hightScore const *>	LoadHightScore::getAllHightScore() const
{
  return (hightScoreList);
}

std::string const			&LoadHightScore::getFileName() const
{
  return (this->fileName);
}

void					LoadHightScore::flush() const
{
  std::ofstream						fd;
  std::vector<t_hightScore const *>::const_iterator	it;
  t_header		        *header = new s_header(sizeof(t_header),
						       sizeof(t_header) +
						       (sizeof(t_hightScore) * hightScoreList.size()), hightScoreList.size());

  fd.open(fileName.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
  if (fd.is_open())
    {
      fd.write(reinterpret_cast<const char *>(header), sizeof(t_header));
      it = hightScoreList.begin();
      while (it != hightScoreList.end())
      	{
      	  fd.write(reinterpret_cast<const char *>(*it), sizeof(t_hightScore));
      	  ++it;
      	}
      fd.close();
      delete header;
    }
}

std::ostream &operator<<(std::ostream &ostream, LoadHightScore const &hightScore)
{
  std::vector<t_hightScore const *>::const_iterator	it;
  const std::vector<t_hightScore const *>		vectorHightScore =
    hightScore.getAllHightScore();

  it = vectorHightScore.begin();
  while (it != vectorHightScore.end())
    {
      ostream << "{" << std::endl << "\t" << "name: \"" << (*it)->getName() << "\"," << std::endl;
      ostream <<  "\t" << "hightScore: " << (*it)->getScore() << std::endl;
      ostream << "}" << std::endl;
      ++it;
    }
  return (ostream);
}
