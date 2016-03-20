//
// Created by gaspar_q on 3/18/16.
//

#include "ArcadeMenu.hpp"
#include "Commons/include/AnimationComponent.hpp"
#include "Commons/include/ArcadeSystem.hpp"

ArcadeMenu::ArcadeMenu(arcade::Arcade &arcade1) :
    arcade1(arcade1)
{
    mode = frames.end();
    frameIdx = 0;
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(Vector2<int>(1, 5),
                                      AComponent::ComponentColor::COLOR_WHITE,
                                      Vector2<int>(20, 3),
                                      "Graphic",
                                      ""
                    ),
                    &arcade::Arcade::onPrevGraph,
                    &arcade::Arcade::onNextGraph
            )
    );
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(
                            Vector2<int>(1, 9),
                            AComponent::ComponentColor::COLOR_WHITE,
                            Vector2<int>(20, 3),
                            "Game",
                            ""
                    ),
                    &arcade::Arcade::onPrevGame,
                    &arcade::Arcade::onNextGame
            )
    );
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(
                            Vector2<int>(1, 13),
                            AComponent::ComponentColor::COLOR_WHITE,
                            Vector2<int>(20, 3),
                            "Play",
                            ""
                    )
            )
    );
    currComponent = menuComponents.begin();
    sysEvents[ArcadeSystem::ArrowDown] = &ArcadeMenu::goDown;
    sysEvents[ArcadeSystem::ArrowUp] = &ArcadeMenu::goUp;
    sysEvents[ArcadeSystem::ArrowLeft] = &ArcadeMenu::prevAction;
    sysEvents[ArcadeSystem::ArrowRight] = &ArcadeMenu::nextAction;
    sysEvents[ArcadeSystem::Enter] = &ArcadeMenu::onEnter;
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

std::stack<AComponent *>        ArcadeMenu::updateMenu(int key)
{
    std::stack<AComponent *>    components;
    std::map<int, ArcadeMenu::menuEvents>::iterator   it;

    if ((it = sysEvents.find(key)) != sysEvents.end())
        (this->*(it->second))();
    components.push(new AnimationComponent(1, 1, AComponent::ComponentColor::COLOR_WHITE, getNextFrame()));
    components.push(new DualTextComponent(*menuComponents[ArcadeMenu::GRAPHIC]));
    components.push(new DualTextComponent(*menuComponents[ArcadeMenu::GAME]));
    components.push(new DualTextComponent(*menuComponents[ArcadeMenu::PLAY]));
    return components;
}

void ArcadeMenu::nextAction()
{
    const arcade::eventSystem eventSystem = (*currComponent).getAction2();

    if (eventSystem != NULL)
    {
        (arcade1.*eventSystem)();
        updateTexts();
    }
}

void ArcadeMenu::prevAction()
{
    const arcade::eventSystem eventSystem = (*currComponent).getAction1();

    if (eventSystem != NULL)
    {
        (arcade1.*eventSystem)();
        updateTexts();
    }
}

void ArcadeMenu::goDown()
{
    (*currComponent).unselect();
    ++currComponent;
    if (currComponent == menuComponents.end())
        currComponent = menuComponents.begin();
    (*currComponent).select();
}

void ArcadeMenu::goUp()
{
    (*currComponent).unselect();
    if (currComponent == menuComponents.begin())
        currComponent = menuComponents.end();
    --currComponent;
    (*currComponent).select();
}

void ArcadeMenu::onEnter()
{
    if (menuComponents[ArcadeMenu::PLAY].isSelected())
        arcade1.setStatus(arcade::Arcade::Game);
    else
        arcade1.setStatus(arcade::Arcade::Menu);
}

void ArcadeMenu::updateTexts()
{
    menuComponents[ArcadeMenu::GRAPHIC]->setSubTitle(arcade1.getCurrentLibName());
    menuComponents[ArcadeMenu::GAME]->setSubTitle(arcade1.getCurrentGameName());
}
