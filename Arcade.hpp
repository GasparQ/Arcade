//
// Created by gaspar_q on 3/9/16.
//

#ifndef C_ARCADE_HPP
#define C_ARCADE_HPP

#include <string>
#include <vector>
#include <regex.h>
#include <map>
#include "Graphique/include/IGraph.hpp"
#include "Game/include/IGame.hpp"

namespace arcade
{
    static const size_t winWidth = 50; // 50
    static const size_t winHeight = 30; // 30

    static const int ArrowLeft = 'q';
    //113;
    static const int ArrowRight = 'd';
    //261;
    static const int ArrowUp = 'z';
    //259;
    static const int ArrowDown = 's';
    //258;
    static const int Space = ' ';

    static const int PrevGraph = '2';
    static const int NextGraph = '3';
    static const int PrevGame = '4';
    static const int NextGame = '5';
    static const int Restart = '8';
    static const int Home = '9';
    static const int Exit = 27;
    static const int Pause = 'P';

    class Arcade;

    typedef void    (Arcade::*eventSystem)();

    class Arcade
    {
    public:
        Arcade();

        ~Arcade();

        static const std::string libDir;
        static const std::string gamesDir;
        static const std::string createLib;
        static const std::string createGame;

      typedef enum {
	Game,
	Menu
      }		Status;
        void Init(std::string const &libname);
        void Run();

    private:
        void onPrevGraph();

        void onNextGraph();

        void onNextGame();

        void onPrevGame();

        void onRestart();

        void onHome();

        void onExit();

        /**
         * Attributes
         */
    private:
        IGraph *lib;
        std::vector<IGame *> games;
        std::vector<IGame *>::iterator currGame;
        std::vector<std::string> libsName;
        std::vector<std::string>::iterator  currLibName;
        std::map<std::string, void *> dlopenedlibs;
        void *dllib;
        std::map<int, arcade::eventSystem> eventSystem;
        bool isRunning;
      Status	_status;
        regex_t lib_names;

        /**
         * Methods
         */
    private:
        bool isLibNameValid(std::string const &, regex_t &) const;

        void loadGraph();
        void findCurrLib(std::string const &libname);

        std::vector<std::string> loadFilesFromDir(std::string const &dirName, regex_t &nameRestric);

        void loadGames(std::vector<std::string> const &);
    };
}

#endif //C_ARCADE_HPP
