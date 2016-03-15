//
// Created by gaspar_q on 3/15/16.
//

#ifndef C_HIGHSCORECOMPONENT_HPP
#define C_HIGHSCORECOMPONENT_HPP

#include "../../Commons/include/AComponent.hpp"
#include "UIComponent.hpp"
#include "LoadHighScore.hpp"

class HighScoreComponent : public AComponent
{
public:
    HighScoreComponent(std::string const &gameName, size_t score);
    virtual ~HighScoreComponent();
    static const std::string    pseudoPlaceholder;
    static const std::string    labelHighscores;
    static const size_t         componentNb = 14;
    static const Vector2<int>   highscoreDim;
    static const Vector2<int>   highscorePos;
    typedef enum
    {
        GAMENAME,
        SCORE,
        PSEUDO,
        LABEL
    } ComponentsPos;

public:
    void                                UpdatePseudo(const int key);
    UIComponent const * const           *getComponentsToDisplay() const;
    void                                submit() const;

private:
    const std::string   gameName;
    std::string         name;
    LoadHighScore       highScores;
    UIComponent         *components[componentNb];
};

#endif //C_HIGHSCORECOMPONENT_HPP
