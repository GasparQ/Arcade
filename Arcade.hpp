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
  static const size_t         winWidth = 50; // 50
  static const size_t         winHeight = 30; // 30

    static const int            ArrowLeft = 260;
    static const int            ArrowRight = 261;
    static const int            ArrowUp = 259;
    static const int            ArrowDown = 258;
    static const int            Space = ' ';

    static const int            PrevGraph = '2';
    static const int            NextGraph = '3';
    static const int            PrevGame = '4';
    static const int            NextGame = '5';
    static const int            Restart = '8';
    static const int            Home = '9';
    static const int            Exit = 27;
    static const int            Pause = 'P';

    class Arcade
    {
    public:
        Arcade(std::string const &);
        ~Arcade();
        static const std::string    libDir;
        static const std::string    gamesDir;

        static const std::string    createLib;
        static const std::string    createGame;
        void                        Run();

        /**
         * Attributes
         */
    private:
        IGraph                          *lib;
        std::vector<IGame *>            games;
        IGame                           *currGame;
        std::vector<std::string>        libsName;
        std::map<std::string, void *>   dlopenedlibs;

        /**
         * Methods
         */
    private:
        bool                        isLibNameValid(std::string const &, regex_t &) const;
        void                        loadGraph(std::string const &);
        std::vector<std::string>    loadFilesFromDir(std::string const &dirName, regex_t &nameRestric);
        void                        loadGames(std::vector<std::string> const &);
    };
}

#endif //C_ARCADE_HPP
