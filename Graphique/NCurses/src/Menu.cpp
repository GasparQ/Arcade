//
// Menu.cpp for Menu in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 10:00:12 2016 Victor Gouet
// Last update Thu Mar 10 14:43:01 2016 Victor Gouet
//

# include "../include/Menu.hpp"

ncr::Menu::Menu(int height, int width, int x, int y, WINDOW *win)
{
  mainWindow = new ncr::Window(height, width, x, y, win);
  _prevSelect = NULL;
}

ncr::Menu::~Menu()
{
  if (mainWindow)
    delete mainWindow;
}

ncr::Window	*ncr::Menu::addSubWin(int height)
{
  ncr::Window	* newWin;

  if (subWin.empty())
    {
      newWin = new ncr::Window(height,
			       mainWindow->getWidth() - 2,
			       mainWindow->getX() + 1,
			       mainWindow->getY() + 1,
			       mainWindow->getWin(), 1);
      subWin.push_back(newWin);
    }
  else
    {
      newWin = new ncr::Window(height, mainWindow->getWidth() - 2,
			       mainWindow->getX() + 1,
			       subWin.back()->getY() + subWin.back()->getHeight(),
			       mainWindow->getWin(),
			       subWin.back()->getId() + 1);
      subWin.push_back(newWin);
    }
  return (newWin);
}

int				ncr::Menu::refresh(int id)
{
  std::list<Window *>::iterator	it;

  it = subWin.begin();
  while (it != subWin.end())
    {
      if ((*it)->getId() == id)
	{
	  (*it)->refresh();
	}
      ++it;
    }
  mainWindow->refresh();
  return (0);
}

int		ncr::Menu::deleteSubWin(int id)
{
  std::list<Window *>::iterator	it;

  it = subWin.begin();
  while (it != subWin.end())
    {
      if ((*it)->getId() == id || id == -1)
	{
	  (*it)->clear();
	  delete *it;
	  it = subWin.erase(it);
	}
      else
	{
	  ++it;
	}
    }
  mainWindow->refresh();
  return (0);
}

int		ncr::Menu::selectWindow(int id)
{
  std::list<Window *>::iterator	it;

  it = subWin.begin();
  if (_prevSelect)
    {
      // (*it)->setAttrOFF(A_REVERSE);
      // (*it)->attrOFF(A_REVERSE);
      wscrl((*it)->getWin(), A_REVERSE);
      _prevSelect->refresh();
      // _prevSelect->clear();
      _prevSelect = NULL;
    }
  while (it != subWin.end())
    {
      if ((*it)->getId() == id || id == -1)
	{
	  // (*it)->clear();
	  // (*it)->setAttrON(A_REVERSE);
	  (*it)->attrON(A_REVERSE);
	  (*it)->print(1, 1, "toto");
	  _prevSelect = *it;
	}
      (*it)->refresh();
      ++it;
    }
  return (0);
}

ncr::Window     *ncr::Menu::getMainWindow() const
{
  return (this->mainWindow);
}
