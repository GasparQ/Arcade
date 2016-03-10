#include <iostream>
#include <unistd.h>
#include "Arcade.hpp"

int main(int ac, char **av)
{
    arcade::Arcade  *arcade;

    if (ac != 2)
    {
        std::cerr << "Not enought args" << std::endl;
        return (1);
    }
    arcade = new arcade::Arcade(av[1]);
    /*try
    {
    }
    catch (std::exception exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }*/
    arcade->Run();
    return 0;
}