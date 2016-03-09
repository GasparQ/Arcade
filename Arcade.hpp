//
// Created by gaspar_q on 3/9/16.
//

#ifndef C_ARCADE_HPP
#define C_ARCADE_HPP

#include <string>
#include <vector>
#include "Graphique/include/IGraph.hpp"
#include "Game/include/IGame.hpp"

namespace arcade
{
    class Arcade
    {
    public:
        Arcade(std::string const &);
        ~Arcade();
        static const std::string    libDir;
        static const std::string    gamesDir;

        static const std::string    createLib;
        static const std::string    createGame;

        /**
         * Attributes
         */
    private:
        IGraph                      *lib;
        std::vector<IGame *>        games;
        std::vector<std::string>    libsName;

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
