//
// Created by gaspar_q on 3/18/16.
//

#include "ArcadeMenu.hpp"

ArcadeMenu::ArcadeMenu()
{
    mode = frames.end();
    frameIdx = 0;
}

ArcadeMenu::~ArcadeMenu()
{

}

void ArcadeMenu::setFrames(const std::string &mode, const std::string &fileprefix, size_t t)
{
    while (--t >= 0)
    {
        frames[mode].push_back(fileprefix + static_cast<char>(t + '0'));
    }
}

void ArcadeMenu::setMode(const std::string &newMode)
{
    std::map<std::string, std::vector<std::string>>::iterator it;

    if ((it = frames.find(newMode)) == frames.end())
        return;
    mode = it;
    frameIdx = 0;
}

std::string const &ArcadeMenu::getNextFrame() const
{
    std::string framename;

    if (mode == frames.end())
        return "";
    framename = mode->second[frameIdx % mode->second.size()];
    frameIdx++;
    return framename;
}
