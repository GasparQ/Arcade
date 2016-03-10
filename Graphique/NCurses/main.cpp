//
// main.cpp for test in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 23:13:36 2016 Victor Gouet
// Last update Thu Mar 10 18:24:37 2016 Victor Gouet
//

#include "./include/Window.hpp"
#include "./include/NCurses.hpp"
#include "./include/Menu.hpp"

# define CARAC '+'
# define BIN '|'
# define BORDER '-'

int	main()
{
  // char	toto[80];

  NCurses::init();
  NCurses::hide_cursor();
  NCurses::noEchoMode();
  

  ncr::Menu	menu(60, 60, 0, 0);

  menu.getMainWindow()->makeBorder(CARAC, CARAC, CARAC);
  // menu.getMainWindow()->attrON(A_REVERSE);
  ncr::Window *win;
  win = menu.addSubWin(10);//.makeBorder('+', '|', '-');
  win->makeBorder(CARAC, CARAC, CARAC);
  menu.addSubWin(3)->makeBorder(CARAC, CARAC, CARAC);
  menu.addSubWin(3)->makeBorder(CARAC, CARAC, CARAC);
  menu.addSubWin(3)->makeBorder(CARAC, CARAC, CARAC);
  menu.addSubWin(3)->makeBorder(CARAC, CARAC, CARAC);
  menu.addSubWin(3)->makeBorder(CARAC, CARAC, CARAC);

  win->setAttrON(A_REVERSE);
  int	i = 0;

  i = 0;
  while (i++ < win->getHeight() * win->getWidth())
    {
      
      win->print("%c", mvwinch(win->getWin(), 0, 0));
    }
  // menu.getMainWindow()->attrOFF(A_REVERSE);
  win->setAttrOFF(A_REVERSE);
  menu.refresh();







  // ncr::Window	win(40, 40, 0, 0);
  // ncr::Window	*subWin = new ncr::Window(38, 38, 1, 1, win);


  // // NCurses::initPair(1, COLOR_CYAN, COLOR_RED);
  // NCurses::initPair(2, COLOR_GREEN, COLOR_GREEN);

  // // win.setColorPair(1);
  // subWin->setColorPair(2);

  // win.attrON(A_REVERSE);
  // win.makeBorder(' ', ' ', ' ');
  // subWin->print(1, 1, "Score: %d", 1000000);
  // win.attrOFF(A_REVERSE);

  // // NCurses::getString(toto);
  // // win.print(1, 2, "%s", toto);
  // // win.refresh();
  // // NCurses::getCarac();
  // // NCurses::initPair(1, COLOR_BLUE, COLOR_BLUE);
  // // win.refresh();
  // NCurses::getCarac();
  // // subWin->clear();
  // // subWin->print(1, 1, "Score: %d", 666);
  // // subWin->refresh();
  // // delete subWin;

  NCurses::getCarac();
  // menu.deleteSubWin(4);
  menu.selectWindow(2);

  // win.clear();
  // win.makeBorder('+', '|', '+');
  // win.print(1, 1, "Hello world");
  // win.refresh();
  NCurses::getCarac();
  menu.selectWindow(1);

  NCurses::getCarac();
  menu.selectWindow(3);
  NCurses::getCarac();
  NCurses::destroy();
}
