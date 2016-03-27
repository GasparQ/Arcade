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
    static const Vector2<double>   highscoreDim;
    static const Vector2<double>   highscorePos;
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
    bool                                submit();

private:
    const std::string   gameName;
    LoadHighScore       highScores;
    size_t              score;
    UIComponent         *components[componentNb];
};

#endif //C_HIGHSCORECOMPONENT_HPP
