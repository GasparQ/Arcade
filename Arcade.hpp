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
#include "Commons/include/Chrono.hpp"
#include "Commons/AudioComponent.hpp"

/**
 * \brief namespace arcade for the entire project
 */
namespace arcade
{
    class Arcade;

    typedef void    (Arcade::*eventSystem)();

    /**
     * \brief core functionment of the project
     */
    class Arcade
    {
    public:
        Arcade();

        ~Arcade();

        static const std::string libDir;
        static const std::string gamesDir;
        static const std::string createLib;
        static const std::string createGame;

        typedef enum
        {
            Game,
            Menu
        } Status;

        void Init(std::string const &libname);

        void Run();

    public:
        void onPrevGraph();

        void onNextGraph();

        void onNextGame();

        void onPrevGame();

        void onRestart();

        void onHome();

        void onExit();

        std::string getCurrentLibName() const;

        std::string getCurrentGameName() const;

        void setStatus(Status);

        /**
         * Attributes
         */
    private:
        IGraph *lib;
        std::vector<IGame *> games;
        std::vector<IGame *>::iterator currGame;
        std::vector<std::string> libsName;
        std::vector<std::string>::iterator currLibName;
        std::map<std::string, void *> dlopenedlibs;
        void *dllib;
        std::map<int, arcade::eventSystem> eventSystem;
        bool isRunning;
        Status _status;
        regex_t lib_names;

        std::stack<AComponent *>    components;
        Chrono<Arcade, void (Arcade::*)()> *chrono_menu;
        /**
         * \brief Used to store all the musics
         */
        AudioComponent audioComponent[1] = {{"Sound/HeyHeyHey.wav", false, false, true}};

        /**
         * Methods
         */
    private:
        bool isLibNameValid(std::string const &, regex_t &) const;

        void loadGraph();

        void findCurrLib(std::string const &libname);

        std::vector<std::string> loadFilesFromDir(std::string const &dirName, regex_t &nameRestric);

        void loadGames(std::vector<std::string> const &);

        void addMenuSound();
    };
}

#endif //C_ARCADE_HPP
