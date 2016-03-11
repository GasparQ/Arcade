//
// Created by gaspar_q on 3/9/16.
//

#include <dlfcn.h>
#include <dirent.h>
#include <regex.h>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iostream>
#include "Arcade.hpp"
#include "Exception/LoadException.hpp"

const std::string    arcade::Arcade::libDir = "./lib/";
const std::string    arcade::Arcade::gamesDir = "./games/";
const std::string    arcade::Arcade::createLib = "loadLib";
const std::string    arcade::Arcade::createGame = "loadGame";

arcade::Arcade::Arcade(std::string const &libname)
{
    regex_t                     reg;
    std::vector<std::string>    gameLibs;

    isRunning = true;
    eventSystem[PrevGame] = &arcade::Arcade::onPrevGame;
    eventSystem[NextGame] = &arcade::Arcade::onNextGame;
    eventSystem[NextGraph] = &arcade::Arcade::onNextGraph;
    eventSystem[PrevGraph] = &arcade::Arcade::onPrevGraph;
    eventSystem[Restart] = &arcade::Arcade::onRestart;
    eventSystem[Home] = &arcade::Arcade::onHome;
    eventSystem[Exit] = &arcade::Arcade::onExit;
    lib = NULL;
    if (regcomp(&reg, "^(.*[\\/])?lib_arcade_[[:alnum:]\\_]+.so$", REG_EXTENDED) != 0)
        throw std::runtime_error("arcade: cannot regcomp");
    libsName = loadFilesFromDir(arcade::Arcade::libDir, reg);
    gameLibs = loadFilesFromDir(arcade::Arcade::gamesDir, reg);
    loadGames(gameLibs);
    if (!isLibNameValid(libname, reg))
        throw arcade::InvalidFileFormatException(libname);
    loadGraph(libname);
}

arcade::Arcade::~Arcade()
{
    std::map<std::string, void *>::iterator it;
    std::map<std::string, void *>::iterator end;

    if (lib)
        delete(lib);
    for (it = dlopenedlibs.begin(), end = dlopenedlibs.end(); it != end; ++it)
    {
        if (it->second && dlclose(it->second) != 0)
            throw std::runtime_error("arcade: cannot close '" + it->first + "' library");
    }
    dlopenedlibs.clear();
}

std::vector<std::string>        arcade::Arcade::loadFilesFromDir(std::string const &dirName, regex_t &nameRestric)
{
    std::vector<std::string>    names;
    DIR                         *directory;
    struct dirent               *pent;

    if ((directory = opendir(dirName.c_str())) == NULL)
        throw std::runtime_error("arcade: cannot open directory '" + dirName + "'");
    while ((pent = readdir(directory)) != NULL)
    {
        if (pent->d_name[0] == '.')
            continue;
        if (!isLibNameValid(pent->d_name, nameRestric))
            throw InvalidFileFormatException(pent->d_name);
        names.push_back(dirName + pent->d_name);
    }
    if (closedir(directory) == -1)
        throw std::runtime_error("arcade: Cannot close directory '" + dirName + "'");
    return names;
}

void        arcade::Arcade::loadGraph(const std::string &libname)
{
    IGraph  *(*load_lib)();

    if (lib)
        delete(lib);
    if ((dlopenedlibs[libname] = dlopen(libname.c_str(), RTLD_LAZY)) == NULL)
        throw LoadLibraryException(libname);
    if ((load_lib = (IGraph *(*)())dlsym(dlopenedlibs[libname], arcade::Arcade::createLib.c_str())) == NULL)
        throw IncompleteLibraryException(libname);//throw error
    lib = load_lib();
}

void        arcade::Arcade::loadGames(const std::vector<std::string> &libsName)
{
    IGame   *(*load_game)();

    for (size_t i = 0, len = libsName.size(); i < len; ++i)
    {
        if ((dlopenedlibs[libsName[i]] = dlopen(libsName[i].c_str(), RTLD_LAZY)) == NULL)
            throw LoadLibraryException(libsName[i]);
        if ((load_game = (IGame *(*)())dlsym(dlopenedlibs[libsName[i]], arcade::Arcade::createGame.c_str())) == NULL)
            throw IncompleteLibraryException(libsName[i]);
        games.push_back(load_game());
    }
    currGame = games.front();
}

bool                    arcade::Arcade::isLibNameValid(const std::string &string, regex_t &reg) const
{
    static regmatch_t   matches[10];

    if (regexec(&reg, string.c_str(), 10, matches, 0) == REG_NOMATCH)
        return false;
    return true;
}

void		arcade::Arcade::onPrevGraph()
{
  
}

void		arcade::Arcade::onNextGraph()
{

}

void		arcade::Arcade::onNextGame()
{

}

void		arcade::Arcade::onPrevGame()
{

}

void		arcade::Arcade::onRestart()
{

}

void		arcade::Arcade::onHome()
{

}

void		arcade::Arcade::onExit()
{
  isRunning = false;
}

void        arcade::Arcade::Run()
{
    int     key;
    std::chrono::milliseconds chrono(100);
    std::map<int, arcade::eventSystem>::iterator	it;

    while (isRunning)
    {
        key = lib->eventManagment();
	if ((it = this->eventSystem.find(key)) != eventSystem.end())
	  (this->*it->second)();
        //TODO check event système
        lib->display(currGame->compute(key));
        //TODO wait
        std::this_thread::sleep_for(chrono);
    }
}
