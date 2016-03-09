//
// main.cpp for test in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 23:13:36 2016 Victor Gouet
// Last update Wed Mar  9 23:50:21 2016 Victor Gouet
//

#include "./include/Window.hpp"

int	main()
{
  initscr();
  ncr::Window	win(40, 40, 0, 0);

  win.attrON(A_REVERSE);
  win.makeBorder(' ', ' ', ' ');
  win.print(1, 1, "Score: %d", 1000000);
  win.attrOFF(A_REVERSE);
  getch();
  endwin();
}
