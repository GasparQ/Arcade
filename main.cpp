#include <iostream>
#include <unistd.h>
#include "Arcade.hpp"

int main(int ac, char **av)
{
    arcade::Arcade  arcade;

    if (ac != 2)
    {
        std::cerr << "\e[1mUsage\e[0m:" << std::endl << "\t./arcade lib_arcade_[libname].so" << std::endl << "\e[1mTip\e[0m:" << std::endl << "\tThere are few libs in \"./lib/\" directory" << std::endl;
        return (1);
    }
    try
    {
        arcade.Init(av[1]);
    }
    catch (std::runtime_error exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    arcade.Run();
    return 0;
}
