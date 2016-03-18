//
// Created by gaspar_q on 3/18/16.
//

#include "ArcadeMenu.hpp"
#include "Commons/include/AnimationComponent.hpp"
#include "Commons/include/ArcadeSystem.hpp"

ArcadeMenu::ArcadeMenu()
{
    mode = frames.end();
    frameIdx = 0;
    menuComponents.push_back(ActionComponent(Vector2<int>(1, 5), AComponent::ComponentColor::COLOR_WHITE, Vector2<int>(20, 3), "Graphic"));
    menuComponents.push_back(ActionComponent(Vector2<int>(1, 8), AComponent::ComponentColor::COLOR_WHITE, Vector2<int>(20, 3), "Game"));
    menuComponents.push_back(ActionComponent(Vector2<int>(1, 11), AComponent::ComponentColor::COLOR_WHITE, Vector2<int>(20, 3), "Play"));
    currComponent = menuComponents.begin();
}

ArcadeMenu::~ArcadeMenu()
{

}

void ArcadeMenu::setFrames(const std::string &mode, const std::string &fileprefix, int t)
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

std::string ArcadeMenu::getNextFrame() const
{
    std::string framename;

    if (mode == frames.end())
        return "";
    framename = mode->second[frameIdx % mode->second.size()];
    frameIdx++;
    return framename;
}

void ArcadeMenu::eventManager(int key, std::string const &currGame, std::string const &currLib)
{
    switch (key)
    {
        case ArcadeSystem::ArrowDown:
            currComponent->unselect();
            ++currComponent;
            if (currComponent == menuComponents.end())
                menuComponents.begin();
            currComponent->select();
            break;
        case ArcadeSystem::ArrowUp:
            currComponent->unselect();
            if (currComponent == menuComponents.begin())
                currComponent = menuComponents.end();
            --currComponent;
            currComponent->select();
            break;
        case ArcadeSystem::ArrowLeft:
            menuComponents[ArcadeMenu::GRAPHIC].setSubTitle(currLib);
            menuComponents[ArcadeMenu::GAME].setSubTitle(currGame);
            break;
        case ArcadeSystem::ArrowRight:
            menuComponents[ArcadeMenu::GRAPHIC].setSubTitle(currLib);
            menuComponents[ArcadeMenu::GAME].setSubTitle(currGame);
            break;
        default:
            break;
    }
}

std::stack<AComponent *>        ArcadeMenu::updateMenu(int key, std::string const &currGame, std::string const &currLib)
{
    std::stack<AComponent *>    components;

    eventManager(key, currGame, currLib);
    components.push(new AnimationComponent(1, 1, AComponent::ComponentColor::COLOR_WHITE, getNextFrame()));
    components.push(new ActionComponent(menuComponents[ArcadeMenu::GRAPHIC]));
    components.push(new ActionComponent(menuComponents[ArcadeMenu::GAME]));
    components.push(new ActionComponent(menuComponents[ArcadeMenu::PLAY]));
    return components;
}
