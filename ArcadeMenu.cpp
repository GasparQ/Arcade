//
// Created by gaspar_q on 3/18/16.
//

#include "ArcadeMenu.hpp"
#include "Commons/include/AnimationComponent.hpp"
#include "Commons/include/ArcadeSystem.hpp"
#include "Commons/include/Chrono.hpp"

ArcadeMenu::ArcadeMenu(arcade::Arcade &arcade1) :
    arcade1(arcade1),
    anim(1, 1, AComponent::COLOR_WHITE, ""),
    m_sound("Sound/Menu.wav", true, false, false)
{
    mode = frames.end();
    frameIdx = 0;
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(Vector2<double>(ArcadeSystem::winWidth / 2 - 10, 5),
                                      AComponent::ComponentColor::COLOR_WHITE,
                                      Vector2<double>(20, 3),
                                      "Graphic"
                    ),
                    &arcade::Arcade::onPrevGraph,
                    &arcade::Arcade::onNextGraph
            )
    );
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(
                            Vector2<double>(ArcadeSystem::winWidth / 2 - 10, 11),
                            AComponent::ComponentColor::COLOR_WHITE,
                            Vector2<double>(20, 3),
                            "Game"
                    ),
                    &arcade::Arcade::onPrevGame,
                    &arcade::Arcade::onNextGame
            )
    );
    menuComponents.push_back(
            ActionComponent<DualTextComponent, arcade::eventSystem >(
                    DualTextComponent(
                            Vector2<double>(ArcadeSystem::winWidth / 2 - 10, 17),
                            AComponent::ComponentColor::COLOR_WHITE,
                            Vector2<double>(20, 3),
                            "Play"
                    )
            )
    );
    currComponent = menuComponents.begin();
    (*currComponent).select();
    (*currComponent)->setColor(AComponent::ComponentColor::COLOR_RED);
    sysEvents[ArcadeSystem::ArrowDown] = &ArcadeMenu::goDown;
    sysEvents[ArcadeSystem::ArrowUp] = &ArcadeMenu::goUp;
    sysEvents[ArcadeSystem::ArrowLeft] = &ArcadeMenu::prevAction;
    sysEvents[ArcadeSystem::ArrowRight] = &ArcadeMenu::nextAction;
    sysEvents[ArcadeSystem::Enter] = &ArcadeMenu::onEnter;
    updateTexts();
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
    std::map<int, ArcadeMenu::menuEvents>::iterator   it;
    std::stack<AComponent *>    components;
    
    if ((it = sysEvents.find(key)) != sysEvents.end())
        (this->*(it->second))();
    updateTexts();
    components.push(&*menuComponents[ArcadeMenu::GRAPHIC]);
    components.push(&*menuComponents[ArcadeMenu::GAME]);
    components.push(&*menuComponents[ArcadeMenu::PLAY]);
    anim.setFileName(getNextFrame());
    components.push(&anim);
    components.push(&m_sound);

    return components;
}

void ArcadeMenu::nextAction()
{
    const arcade::eventSystem eventSystem = (*currComponent).getAction2();

    if (eventSystem != NULL)
        (arcade1.*eventSystem)();
}

void ArcadeMenu::prevAction()
{
    const arcade::eventSystem eventSystem = (*currComponent).getAction1();

    if (eventSystem != NULL)
        (arcade1.*eventSystem)();
}

void ArcadeMenu::goDown()
{
    (*currComponent).unselect();
    (*currComponent)->setColor(AComponent::ComponentColor::COLOR_WHITE);
    ++currComponent;
    if (currComponent == menuComponents.end())
        currComponent = menuComponents.begin();
    (*currComponent).select();
    (*currComponent)->setColor(AComponent::ComponentColor::COLOR_RED);
}

void ArcadeMenu::goUp()
{
    (*currComponent).unselect();
    (*currComponent)->setColor(AComponent::ComponentColor::COLOR_WHITE);
    if (currComponent == menuComponents.begin())
        currComponent = menuComponents.end();
    --currComponent;
    (*currComponent).select();
    (*currComponent)->setColor(AComponent::ComponentColor::COLOR_RED);
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
