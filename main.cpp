#include <iostream>
#include <unistd.h>
#include "Arcade.hpp"

int main(int ac, char **av)
{
    arcade::Arcade  arcade;

    if (ac != 2)
    {
        std::cerr << "Not enought args" << std::endl;
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
