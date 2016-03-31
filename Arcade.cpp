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
#include <algorithm>
#include <fstream>
#include "Arcade.hpp"
#include "Exception/LoadException.hpp"
#include "Commons/include/ArcadeSystem.hpp"
#include "ArcadeMenu.hpp"

const std::string    arcade::Arcade::libDir = "./lib/";
const std::string    arcade::Arcade::gamesDir = "./games/";
const std::string    arcade::Arcade::createLib = "loadLib";
const std::string    arcade::Arcade::createGame = "loadGame";

arcade::Arcade::Arcade()
{
    _status = Arcade::Menu;
    isRunning = true;
    eventSystem[ArcadeSystem::PrevGame] = &arcade::Arcade::onPrevGame;
    eventSystem[ArcadeSystem::NextGame] = &arcade::Arcade::onNextGame;
    eventSystem[ArcadeSystem::NextGraph] = &arcade::Arcade::onNextGraph;
    eventSystem[ArcadeSystem::PrevGraph] = &arcade::Arcade::onPrevGraph;
    eventSystem[ArcadeSystem::Restart] = &arcade::Arcade::onRestart;
    eventSystem[ArcadeSystem::Home] = &arcade::Arcade::onHome;
    eventSystem[ArcadeSystem::Exit] = &arcade::Arcade::onExit;
    lib = NULL;
    dllib = NULL;
    currGame = games.end();
    if (regcomp(&lib_names, "^(.*[\\/])?lib_arcade_[[:alnum:]\\_]+.so$", REG_EXTENDED) != 0)
        throw std::runtime_error("arcade: cannot regcomp");
    libsName = loadFilesFromDir(arcade::Arcade::libDir, lib_names);
    currLibName = libsName.end();
}

arcade::Arcade::~Arcade()
{

    if (lib)
    {
        delete (lib);
        dlclose(dllib);
    }
    for (std::vector<IGame *>::iterator it = games.begin(), end = games.end(); it != end; ++it)
    {
        if (*it != NULL)
            delete(*it);
    }
    for (std::map<std::string, void *>::iterator it = dlopenedlibs.begin(), end = dlopenedlibs.end(); it != end; ++it)
    {
        if (it->second && dlclose(it->second) != 0)
            throw std::runtime_error("arcade: cannot close '" + it->first + "' library");
    }
    dlopenedlibs.clear();
    regfree(&lib_names);
}

void arcade::Arcade::Init(std::string const &libname)
{
    std::vector<std::string>            gameLibs;

    gameLibs = loadFilesFromDir(arcade::Arcade::gamesDir, lib_names);
    loadGames(gameLibs);
    if (!isLibNameValid(libname, lib_names))
        throw arcade::InvalidFileFormatException(libname);
    findCurrLib(libname);
    loadGraph();
}

void arcade::Arcade::findCurrLib(std::string const &libname)
{
    std::vector<std::string>::iterator it;

    for (it = libsName.begin(); it != libsName.end(); ++it)
    {
        if (it->find(libname) != std::string::npos)
        {
            currLibName = it;
            break;
        }
    }
    if (it == libsName.end())
    {
        libsName.push_back(libname);
        currLibName = libsName.end() - 1;
    }
}

std::vector<std::string>        arcade::Arcade::loadFilesFromDir(std::string const &dirName, regex_t &nameRestric)
{
    std::vector<std::string> names;
    DIR *directory;
    struct dirent *pent;

    if ((directory = opendir(dirName.c_str())) == NULL)
        throw std::runtime_error("arcade: cannot open directory '" + dirName + "'");
    while ((pent = readdir(directory)) != NULL)
    {
        if (pent->d_name[0] == '.' || !isLibNameValid(pent->d_name, nameRestric))
            continue;
        names.push_back(dirName + pent->d_name);
    }
    if (closedir(directory) == -1)
        throw std::runtime_error("arcade: Cannot close directory '" + dirName + "'");
    return names;
}

void        arcade::Arcade::loadGraph()
{
    IGraph *(*load_lib)();

    if (lib)
    {
        delete (lib);
        dlclose(dllib);
    }
    if ((dllib = dlopen(currLibName->c_str(), RTLD_NOW)) == NULL)
    {
        throw LoadLibraryException(dlerror());
    }
    if ((load_lib = (IGraph *(*)()) dlsym(dllib, arcade::Arcade::createLib.c_str())) == NULL)
        throw IncompleteLibraryException(*currLibName);
    lib = load_lib();
}

void        arcade::Arcade::loadGames(const std::vector<std::string> &libsName)
{
    IGame *(*load_game)();

    for (size_t i = 0, len = libsName.size(); i < len; ++i)
    {
        if ((dlopenedlibs[libsName[i]] = dlopen(libsName[i].c_str(), RTLD_NOW)) == NULL)
            throw LoadLibraryException(libsName[i] + dlerror());
        if ((load_game = (IGame *(*)()) dlsym(dlopenedlibs[libsName[i]], arcade::Arcade::createGame.c_str())) == NULL)
            throw IncompleteLibraryException(libsName[i]);
        games.push_back(load_game());
    }
    currGame = games.begin();
}

bool                    arcade::Arcade::isLibNameValid(const std::string &string, regex_t &reg) const
{
    static regmatch_t matches[10];

    if (regexec(&reg, string.c_str(), 10, matches, 0) == REG_NOMATCH)
        return false;
    return true;
}

void        arcade::Arcade::onPrevGraph()
{
    if (currLibName == libsName.end())
        return;
    if (currLibName == libsName.begin())
        currLibName = libsName.end();
    --currLibName;
    loadGraph();
}

void        arcade::Arcade::onNextGraph()
{
    if (currLibName == libsName.end())
        return;
    ++currLibName;
    if (currLibName == libsName.end())
        currLibName = libsName.begin();
    loadGraph();
}

void        arcade::Arcade::onNextGame()
{
    if (currGame == games.end())
        return;
    ++currGame;
    if (currGame == games.end())
        currGame = games.begin();
}

void        arcade::Arcade::onPrevGame()
{
    if (currGame == games.end())
        return;
    if (currGame == games.begin())
        currGame = games.end();
    --currGame;
}

void        arcade::Arcade::onRestart()
{
    (*currGame)->restart();
    lib->display(std::stack<AComponent *>());
}

void        arcade::Arcade::onHome()
{
    _status = Arcade::Menu;
}

void        arcade::Arcade::onExit()
{
    isRunning = false;
}

void        arcade::Arcade::Run()
{
    int key;
    std::chrono::milliseconds chrono(10);
    std::map<int, arcade::eventSystem>::iterator it;
    ArcadeMenu  menu(*this);
    std::ofstream   file("debug.log");

    menu.setFrames("text", "./Animation/NcursesAnimation", 4);
    menu.setMode("text");
    while (isRunning)
    {
        std::stack<AComponent *>    components;

        try
        {
            key = lib->eventManagment();
            if (file.is_open())
                file << getCurrentLibName() << ": " << key << std::endl;
        }
        catch (std::exception exception)
        {
            std::cerr << exception.what() << std::endl;
            return;
        }
        if ((it = this->eventSystem.find(key)) != eventSystem.end())
            (this->*it->second)(); // on gere les event system ici
        if (_status == Arcade::Menu)
        {
            components = menu.updateMenu(key);
	    }
        if (_status == Arcade::Game && currGame != games.end())
        {
            components = (*currGame)->compute(key);
        }
        lib->display(components);
        std::this_thread::sleep_for(chrono);
    }
    file.close();
}

std::string arcade::Arcade::getCurrentLibName() const
{
    if (currLibName == libsName.end())
        return ("No such lib");
    return *currLibName;
}

std::string arcade::Arcade::getCurrentGameName() const
{
    if (currGame == games.end())
        return ("No such game");
    return (*currGame)->getName();
}

void arcade::Arcade::setStatus(arcade::Arcade::Status status)
{
    _status = status;
}
