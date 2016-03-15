//
// Created by gaspar_q on 3/15/16.
//

#include "../include/HighScoreComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

const std::string   HighScoreComponent::pseudoPlaceholder("Enter your pseudo");
const std::string   HighScoreComponent::labelHighscores("Highscores");
const Vector2<int>  HighScoreComponent::highscoreDim(15, 20);
const Vector2<int>  HighScoreComponent::highscorePos(7, 5);

static std::string  pseudo(HighScoreComponent::pseudoPlaceholder);

HighScoreComponent::HighScoreComponent(std::string const &gameName, size_t score) :
    AComponent(HighScoreComponent::highscorePos, AComponent::ComponentColor::COLOR_WHITE),
    gameName(gameName),
    highScores(gameName + ".arcade"),
    score(score)
{
    int                                     mid = ArcadeSystem::winWidth / 2;
    const std::vector<const t_highScore *>  scores = highScores.getAllHighScore();
    std::string                             scoreStr("score : ");

    scoreStr += score;
    //Nom du jeu
    components[ComponentsPos::GAMENAME] = new UIComponent(
            Vector2<int>(mid - static_cast<int>(gameName.length()) / 2, 0),
            AComponent::ComponentColor::COLOR_WHITE,
            Vector2<int>(static_cast<int>(gameName.length()), 1),
            gameName
    );
    //Enter you pseudo
    components[ComponentsPos::PSEUDO] = new UIComponent(
            Vector2<int>(mid - static_cast<int>(pseudoPlaceholder.length()) / 2, 2),
            AComponent::ComponentColor::COLOR_WHITE,
            Vector2<int>(static_cast<int>(pseudoPlaceholder.length()), 1),
            HighScoreComponent::pseudoPlaceholder
    );
    //Score
    components[HighScoreComponent::ComponentsPos::SCORE] = new UIComponent(
            Vector2<int>(static_cast<int>(ArcadeSystem::winWidth) / 2 - static_cast<int>(scoreStr.length()) / 2, 1),
            AComponent::ComponentColor::COLOR_WHITE,
            Vector2<int>(static_cast<int>(scoreStr.length()), 1),
            scoreStr
    );
    //Highscores label
    components[ComponentsPos::LABEL] = new UIComponent(
            Vector2<int>(mid - static_cast<int>(HighScoreComponent::labelHighscores.length()) / 2, 3),
            AComponent::ComponentColor::COLOR_WHITE,
            Vector2<int>(static_cast<int>(HighScoreComponent::labelHighscores.length()), 1),
            HighScoreComponent::labelHighscores
    );
    // All scores
    for (int i = 0, len = static_cast<int>(scores.size()); i < 10; ++i)
    {
        if (i < len)
        {
            std::string displayed = scores[i]->getName() + " ";
            displayed += scores[i]->getScore();
            components[i + 3] = new UIComponent(
                    Vector2<int>(mid - static_cast<int>(displayed.length()) / 2, i + 3),
                    AComponent::ComponentColor::COLOR_WHITE,
                    Vector2<int>(static_cast<int>(displayed.length()), 1),
                    displayed
            );
        }
        else
            components[i + 3] = NULL;
    }
}

HighScoreComponent::~HighScoreComponent()
{
    for (size_t i = 0; i < HighScoreComponent::componentNb && components[i] != NULL; ++i)
    {
        delete(components[i]);
    }
}

void HighScoreComponent::UpdatePseudo(const int key)
{
    if (key == ArcadeSystem::Backspace)
    {
        if (!pseudo.empty() && pseudo != HighScoreComponent::pseudoPlaceholder)
            pseudo = pseudo.substr(0, pseudo.length() - 1);
    }
    else if (key >= ' ' && key <= '~' && pseudo.length() < 20)
    {
        if (pseudo == HighScoreComponent::pseudoPlaceholder)
            pseudo.clear();
        pseudo.push_back(static_cast<char>(key));
    }

    if (pseudo.empty())
        pseudo = HighScoreComponent::pseudoPlaceholder;
    delete(components[HighScoreComponent::ComponentsPos::PSEUDO]);
    components[HighScoreComponent::ComponentsPos::PSEUDO] = new UIComponent(
            Vector2<int>(static_cast<int>(ArcadeSystem::winWidth) / 2 - static_cast<int>(pseudo.length()) / 2, 2),
            AComponent::ComponentColor::COLOR_WHITE,
            Vector2<int>(static_cast<int>(pseudo.length()), 1),
            pseudo
    );
}

UIComponent const * const *HighScoreComponent::getComponentsToDisplay() const
{
    return components;
}

bool    HighScoreComponent::submit()
{
    if (pseudo.empty() || pseudo == HighScoreComponent::pseudoPlaceholder)
        return false;
    highScores.setHighScore(new t_highScore(score, pseudo));
    highScores.flush();
    pseudo = HighScoreComponent::pseudoPlaceholder;
    return true;
}