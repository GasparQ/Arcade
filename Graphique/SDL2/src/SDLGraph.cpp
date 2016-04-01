//
// Created by gaspar_q on 3/11/16.
//

#include <unistd.h>
#include "SDLGraph.hpp"
#include "../../../Commons/include/ArcadeSystem.hpp"
#include "../../../Commons/include/DualTextComponent.hpp"
#include "../../../Commons/AudioComponent.hpp"

const std::string SDLGraph::fontName = "./fonts/arcade_barbarian.ttf"; /*arcade_fluid.ttf arcade_font.ttf arcade_boxes.ttf ka1.ttf Minecraft.ttf*/
const std::string SDLGraph::defaultFont = "/usr/share/fonts/truetype/DroidSans-Bold.ttf";

/**
 * \brief Constructor in which SDL, TTF, render, window, font, colors, keycodes will be initialised
 */
SDLGraph::SDLGraph()
{
    if (SDL_Init(0) != 0 ||
        (win = SDL_CreateWindow("Arcade", 0, 0, ArcadeSystem::winWidth * SDLGraph::scale, ArcadeSystem::winHeight * SDLGraph::scale, SDL_WINDOW_SHOWN)) == NULL ||
        (render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == NULL ||
        TTF_Init() != 0 || ((uifont = TTF_OpenFont(SDLGraph::fontName.c_str(), 24)) == NULL &&
        (uifont = TTF_OpenFont(SDLGraph::defaultFont.c_str(), 24)) == NULL))
        throw std::runtime_error(SDL_GetError());
    addColor(AComponent::ComponentColor::COLOR_RED, 174, 10, 15);
    addColor(AComponent::ComponentColor::COLOR_WHITE, 241, 241, 241);
    addColor(AComponent::ComponentColor::COLOR_BLUE, 60, 119, 222);
    addColor(AComponent::ComponentColor::COLOR_CYAN, 0, 193, 177);
    addColor(AComponent::ComponentColor::COLOR_GREEN, 53, 196, 107);
    addColor(AComponent::ComponentColor::COLOR_MAGENTA, 205, 22, 134);
    addColor(AComponent::ComponentColor::COLOR_YELLOW, 225, 207, 10);
    keyCodeAssociation[SDL_SCANCODE_LEFT] = ArcadeSystem::ArrowLeft;
    keyCodeAssociation[SDL_SCANCODE_RIGHT] = ArcadeSystem::ArrowRight;
    keyCodeAssociation[SDL_SCANCODE_UP] = ArcadeSystem::ArrowUp;
    keyCodeAssociation[SDL_SCANCODE_DOWN] = ArcadeSystem::ArrowDown;
    keyCodeAssociation[SDL_SCANCODE_SPACE] = ArcadeSystem::Space;
    keyCodeAssociation[SDL_SCANCODE_2] = ArcadeSystem::PrevGraph;
    keyCodeAssociation[SDL_SCANCODE_3] = ArcadeSystem::NextGraph;
    keyCodeAssociation[SDL_SCANCODE_4] = ArcadeSystem::PrevGame;
    keyCodeAssociation[SDL_SCANCODE_5] = ArcadeSystem::NextGame;
    keyCodeAssociation[SDL_SCANCODE_8] = ArcadeSystem::Restart;
    keyCodeAssociation[SDL_SCANCODE_9] = ArcadeSystem::Home;
    keyCodeAssociation[SDL_SCANCODE_ESCAPE] = ArcadeSystem::Exit;
    keyCodeAssociation[SDL_SCANCODE_P] = ArcadeSystem::Pause;
    keyCodeAssociation[SDL_SCANCODE_RETURN] = ArcadeSystem::Enter;
    keyCodeAssociation[SDL_SCANCODE_BACKSPACE] = ArcadeSystem::Backspace;
}

/**
 * \brief Destructor of SDL lib that will Quit SDL, Quit TTF, close windows, fonts, destroy renderers and cache textures
 */
SDLGraph::~SDLGraph()
{
    std::map<std::string, SDL_Texture*>::iterator   it;

    for (it = spriteCache.begin(); it != spriteCache.end(); ++it)
    {
        SDL_DestroyTexture(it->second);
    }
    TTF_CloseFont(uifont);
    TTF_Quit();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

/**
 * \brief Used to add a color to SDL palette
 * \param index Color of the component
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 */
void SDLGraph::addColor(AComponent::ComponentColor index, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color   color;

    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    colors[index] = color;
}

/**
 * \brief Function that will handle a SDL keycode
 *
 * \return keycode handled
 */
int SDLGraph::eventManagment()
{
    std::map<int, int>::const_iterator  it;
    int                                 key = -1;

    while (SDL_PollEvent(&event) == 1)
    {
        if (event.type == SDL_KEYDOWN)
        {
            key = event.key.keysym.sym;
            if ((it = keyCodeAssociation.find(event.key.keysym.scancode)) != keyCodeAssociation.end())
                return it->second;
        }
    }
    return key;
}

/**
 * \brief Function that will display all of the components send in parameters to the screen
 *
 * \param stack A stack of components to display
 */
void SDLGraph::display(std::stack<AComponent *> stack)
{
    GameComponent       *gameComponent;
    UIComponent         *uiComponent;
    HighScoreComponent  *highScoreComponent;
    AudioComponent *audioComponent;

    SDL_RenderClear(render);
    while (!stack.empty())
    {
        if ((gameComponent = dynamic_cast<GameComponent *>(stack.top())))
            drawGameComponent(gameComponent);
        else if ((uiComponent = dynamic_cast<UIComponent *>(stack.top())))
            drawUIComponent(uiComponent);
        else if ((highScoreComponent = dynamic_cast<HighScoreComponent *>(stack.top())))
            drawHighScoreComponent(highScoreComponent);
        else if ((audioComponent = dynamic_cast<AudioComponent*>(stack.top())))
            m_sound.PlaySound(audioComponent->getSoundPath(), audioComponent->getLoop(),
                              audioComponent->getOverlap(), audioComponent->getStop());
        stack.pop();
    }
    SDL_RenderPresent(render);
}

/**
 * \brief function that will load a sprite from his filename, if a error occur it throws an exception. It save it into a cache.
 *
 * \param file The filename
 * \return The texture corresponding to the sprite loaded
 */
SDL_Texture     *SDLGraph::loadSprite(const std::string &file) throw(std::runtime_error)
{
    std::map<std::string, SDL_Texture*>::iterator   it;

    if ((it = spriteCache.find(file)) != spriteCache.end())
        return (it->second);

    SDL_Surface *surface;
    SDL_Texture *tex;

    if ((surface = SDL_LoadBMP(file.c_str())) == NULL ||
        (tex = SDL_CreateTextureFromSurface(render, surface)) == NULL)
        throw std::runtime_error(SDL_GetError());
    spriteCache[file] = tex;
    SDL_FreeSurface(surface);
    return tex;
}

/**
 * \brief Function that will draw a surface on the screen. It throws an exception if display fails.
 *
 * \param texture The texture to display
 * \param pos The position to which display the surface
 * \param dim The size of the texture
 */
void SDLGraph::displaySurface(SDL_Texture *texture, Vector2<double> pos, Vector2<double> dim) throw(std::runtime_error)
{
    SDL_Rect    sdlRect;

    sdlRect.x = static_cast<int>(pos.x * SDLGraph::scale);
    sdlRect.y = static_cast<int>(pos.y * SDLGraph::scale);
    sdlRect.w = static_cast<int>(dim.x * SDLGraph::scale);
    sdlRect.h = static_cast<int>(dim.y * SDLGraph::scale);
    if (SDL_RenderCopy(render, texture, NULL, &sdlRect) != 0)
        throw std::runtime_error(SDL_GetError());
}

/**
 * \brief Draw a game component on the screen, if loadSprite fails, create a colored square texture. Throws an exception if the drawing fails
 *
 * \param component The component to draw
 */
void SDLGraph::drawGameComponent(GameComponent const *component) throw(std::runtime_error)
{
    SDL_Texture *texture;

    try
    {
        texture = loadSprite(component->getSprite2D());
    }
    catch (std::runtime_error exception)
    {
        SDL_Surface *surface;
        SDL_Rect    rect;
        Uint32      color = 0;
        SDL_Color   compColor = colors[component->getColor()];

        color |= compColor.a << 24;
        color |= compColor.r << 16;
        color |= compColor.g << 8;
        color |= compColor.b;
        rect.x = 0;
        rect.y = 0;
        rect.w = SDLGraph::scale;
        rect.h = SDLGraph::scale;
        if ((surface = SDL_CreateRGBSurface(0, SDLGraph::scale, SDLGraph::scale, 32, 0, 0, 0, 0)) == NULL ||
            (SDL_FillRect(surface, &rect, color)) < 0 ||
            (texture = SDL_CreateTextureFromSurface(render, surface)) == NULL)
            throw std::runtime_error(SDL_GetError());
        SDL_FreeSurface(surface);
        spriteCache[component->getSprite2D()] = texture;
    }
    displaySurface(texture, component->getPos());
}

/**
 * \brief Draw an highscore component. If drawing fails, throws an exceptions.
 *
 * \param component The component to draw
 */
void                            SDLGraph::drawHighScoreComponent(HighScoreComponent const *component) throw(std::runtime_error)
{
    SDL_Surface                 *surface;
    SDL_Texture                 *texture;
    SDL_Rect                    dim;
    UIComponent const * const   *components;

    dim.x = static_cast<int>(component->getPos().x * SDLGraph::scale);
    dim.y = static_cast<int>(component->getPos().y * SDLGraph::scale);
    dim.w = static_cast<int>(HighScoreComponent::highscoreDim.x * SDLGraph::scale);
    dim.h = static_cast<int>(HighScoreComponent::highscoreDim.y * SDLGraph::scale);
    surface = SDL_CreateRGBSurface(
            0,
            static_cast<int>(HighScoreComponent::highscoreDim.x * SDLGraph::scale),
            static_cast<int>(HighScoreComponent::highscoreDim.y * SDLGraph::scale),
            32, 0, 0, 0, 0
    );
    if (surface == NULL ||
        (texture = SDL_CreateTextureFromSurface(render, surface)) == NULL ||
        SDL_RenderCopy(render, texture, NULL, &dim) != 0)
        throw std::runtime_error(SDL_GetError());
    components = component->getComponentsToDisplay();
    for (size_t i = 0; components[i] != NULL; ++i)
    {
        drawUIComponent(components[i]);
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * \brief function to draw text on the screen. Throws an exception if fails.
 *
 * \param string The text to display
 * \param pos The position of the text on the screen
 * \param dim The size of the text in Unit
 * \param color The color of the text
 */
void SDLGraph::drawText(const std::string &string, Vector2<double> pos, Vector2<double> dim, AComponent::ComponentColor color)
{
    SDL_Surface *text;
    SDL_Texture *texture;

    if (string.empty())
        return;
    if ((text = TTF_RenderText_Solid(uifont, string.c_str(), colors[color])) == NULL ||
        (texture = SDL_CreateTextureFromSurface(render, text)) == NULL)
        throw std::runtime_error(SDL_GetError());
    displaySurface(texture, pos, dim);
}

/**
 * \brief Draw an UIComponent on the screen(DualTextComponent is also supported). Throws an exception if failure occurs.
 *
 * \param component The UIComponent to display
 */
void SDLGraph::drawUIComponent(UIComponent const *component) throw(std::runtime_error)
{
    DualTextComponent const   *dualTextComponent = dynamic_cast<DualTextComponent const *>(component);

    drawText(component->getText(), component->getPos(), component->getDim(), component->getColor());
    if (dualTextComponent != NULL)
        drawText(dualTextComponent->getSubTitle(), dualTextComponent->getSubPos(), dualTextComponent->getSubDim());
}

/**
 * \brief Function to instantiate the lib.
 */
extern "C" IGraph *loadLib()
{
    return (new SDLGraph());
}
