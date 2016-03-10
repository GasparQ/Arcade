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
    if (lib)
        delete(lib);
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
    void    *newLib;
    IGraph  *(*load_lib)();

    if (lib)
        delete(lib);
    if ((newLib = dlopen(libname.c_str(), RTLD_NOW)) == NULL)
        throw LoadLibraryException(libname);
    if ((load_lib = (IGraph *(*)())dlsym(newLib, arcade::Arcade::createLib.c_str())) == NULL)
        throw IncompleteLibraryException(libname);//throw error
    std::cout << "lib: " << lib << std::endl;
    lib = load_lib();
    std::cout << "lib: " << lib << std::endl;
    if (dlclose(newLib) != 0)
        throw std::runtime_error("arcade: cannot close '" + libname + "' library");
}

void        arcade::Arcade::loadGames(const std::vector<std::string> &libsName)
{
    void    *gameLib;
    IGame   *(*load_game)();

    for (size_t i = 0, len = libsName.size(); i < len; ++i)
    {
        if ((gameLib = dlopen(libsName[i].c_str(), RTLD_LAZY)) == NULL)
        {
            throw LoadLibraryException(libsName[i]);
        }
        if ((load_game = (IGame *(*)())dlsym(gameLib, arcade::Arcade::createGame.c_str())) == NULL)
            throw IncompleteLibraryException(libsName[i]);
        games.push_back(load_game());
        if (dlclose(gameLib) != 0)
            throw std::runtime_error("arcade: cannot close '" + libsName[i] + "'");
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

void        arcade::Arcade::Run()
{
    int     key;
    std::chrono::seconds chrono(1);

    while (1)
    {
        std::cout << "lib: " << lib << std::endl;

        key = lib->eventManagment();
        //TODO check event système
//        currGame->compute(42);
//        lib->display(currGame->compute(key));
        //TODO wait
        std::this_thread::sleep_for(chrono);
    }
}
