//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ARCADEMENU_HPP
#define C_ARCADEMENU_HPP

#include <stddef.h>
#include <vector>
#include <string>
#include <map>

class ArcadeMenu
{
public:
    ArcadeMenu();
    ~ArcadeMenu();

public:
    void setFrames(std::string const &, std::string const &, size_t );
    void setMode(std::string const &);
    std::string const &getNextFrame() const;

private:
    std::map<std::string, std::vector<std::string>>             frames;
    mutable size_t                                              frameIdx;
    std::map<std::string, std::vector<std::string>>::iterator   mode;
};

#endif //C_ARCADEMENU_HPP
