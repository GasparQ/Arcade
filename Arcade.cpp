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

/**
 * \brief Constants for directories and symbols
 */
const std::string    arcade::Arcade::libDir = "./lib/";
const std::string    arcade::Arcade::gamesDir = "./games/";
const std::string    arcade::Arcade::createLib = "loadLib";
const std::string    arcade::Arcade::createGame = "loadGame";

/**
 * \brief Arcade constructor for the initialisations of the main program
 */
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

    chrono_menu = new Chrono<Arcade, void (Arcade::*)()>(2.7, *this, &Arcade::addMenuSound, "chronoSound");
}

/**
 * \brief Destructor of core program, free the memory
 */
arcade::Arcade::~Arcade()
{
    if (chrono_menu)
    {
        delete chrono_menu;
    }
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

/**
 * \brief Function for the initialisation of the core program. Throws an exception if something fails.
 *
 * \param libname The name of the lib send in program parameter
 */
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

/**
 * \brief Set currLibName iterator from the libname
 *
 * \param libname The libname to search in libList
 */
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

/**
 * \brief Load files from a directory send in parameters. Filter files from regex pattern.
 *
 * \param dirName The name of the directory in which find files
 * \param nameRestric Pattern which filename has to respect
 * \return Vector of filenames
 */
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

/**
 * \brief Load graphic lib from currLibName. Throws an exception if an error occurs
 */
void        arcade::Arcade::loadGraph()
{
    IGraph *(*load_lib)();

    if (lib)
    {
        delete (lib);
    }
    if (dllib)
    {
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

/**
 * \brief Load games from libsName and put them in a vector and IGames *
 *
 * \param libsName Vector of game lib name
 */
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

/**
 * \brief Check if the name of a lib is valid in function of a regex pattern
 *
 * \param string The lib name to check
 * \param reg The regex pattern for libs
 * \return Either the lib name is valid return true or false
 */
bool                    arcade::Arcade::isLibNameValid(const std::string &string, regex_t &reg) const
{
    static regmatch_t matches[10];

    if (regexec(&reg, string.c_str(), 10, matches, 0) == REG_NOMATCH)
        return false;
    return true;
}

/**
 * \brief Function to change the graphical lib to the previous one
 */
void        arcade::Arcade::onPrevGraph()
{
    if (currLibName == libsName.end())
        return;
    if (currLibName == libsName.begin())
        currLibName = libsName.end();
    --currLibName;
    if (_status == Arcade::Menu)
        chrono_menu->ResetChrono();
    loadGraph();
}

/**
 * \brief Function to change the graphical lib to the next one
 */
void        arcade::Arcade::onNextGraph()
{
    if (currLibName == libsName.end())
        return;
    ++currLibName;
    if (currLibName == libsName.end())
        currLibName = libsName.begin();
    /// Resets the chrono for the sound
    if (_status == Arcade::Menu)
        chrono_menu->ResetChrono();
    loadGraph();
}

/**
 * \brief Function to change the game to the next one
 */
void        arcade::Arcade::onNextGame()
{
    m_gameChanged = true;
    if (currGame == games.end())
        return;
    ++currGame;
    if (currGame == games.end())
        currGame = games.begin();
}

/**
 * \brief Function to change the game on the previous one
 */
void        arcade::Arcade::onPrevGame()
{
    m_gameChanged = true;
    if (currGame == games.end())
        return;
    if (currGame == games.begin())
        currGame = games.end();
    --currGame;
}

/**
 * \brief Function to restart the game
 */
void        arcade::Arcade::onRestart()
{
    (*currGame)->restart();
    lib->display(std::stack<AComponent *>());
}

/**
 * \brief Function to return to the home menu
 */
void        arcade::Arcade::onHome()
{
    _status = Arcade::Menu;
}

/**
 * \brief Function to exit the program
 */
void        arcade::Arcade::onExit()
{
    isRunning = false;
}

/**
 * \brief Function to play the sound on the main menu
 */
void arcade::Arcade::addMenuSound()
{
    for (int i = 0; i < 13; i++)
    {
        audioOpening[i].setStop(false);
    }
    components.push(&audioOpening[rand() % 13]);
}

/**
 * \brief Main loop of the program
 */
void        arcade::Arcade::Run()
{
    int key = -1;
    std::chrono::milliseconds chrono(10);
    std::map<int, arcade::eventSystem>::iterator it;
    AudioComponent m_audio_stop("Sound/Menu.wav", false, false, true);
    ArcadeMenu  menu(*this);

    menu.setFrames("text", "./Animation/NcursesAnimation", 4);
    menu.setMode("text");
    while (isRunning)
    {
        try
        {
            if (lib)
                key = lib->eventManagment();
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

            /// We stop all the musics from the games
            for (int i = 0; i < 4; i++)
            {
                components.push(&audioComponent[i]);
            }

            // We update the chrono to trigger the 'Arcaaaaaade' sound
            chrono_menu->Update();
            if (chrono_menu->GetRemainingTime() == 0 && !chrono_menu->HasTriggered())
            {
                chrono_menu->TriggerEvent();
            }
	    }
        if (_status == Arcade::Game && currGame != games.end())
        {
            components = (*currGame)->compute(key);
            /// stops the menu's music
            components.push(&m_audio_stop);
            chrono_menu->ResetChrono();
            /// And we stop all the opening sounds
            for (int i = 0; i < 13; i++)
            {
                audioOpening[i].setStop(true);
                components.push(&audioOpening[i]);
            }
        }

        if (m_gameChanged)
        {
            m_gameChanged = false;
            /// We stop all the musics from the games
            for (int i = 0; i < 4; i++)
            {
                components.push(&audioComponent[i]);
            }
        }

        lib->display(components);
        std::this_thread::sleep_for(chrono);
    }
}

/**
 * \brief Getter for the current lib name
 *
 * \return The current lib name
 */
std::string arcade::Arcade::getCurrentLibName() const
{
    if (currLibName == libsName.end())
        return ("No such lib");
    return *currLibName;
}

/**
 * \brief Getter for the current game name
 *
 * \return The current game name
 */
std::string arcade::Arcade::getCurrentGameName() const
{
    if (currGame == games.end())
        return ("No such game");
    return (*currGame)->getName();
}

/**
 * \brief Setter for the status
 *
 * \param status The new status to set
 */
void arcade::Arcade::setStatus(arcade::Arcade::Status status)
{
    _status = status;
}
