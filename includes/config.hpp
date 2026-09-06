#pragma once

# include "GameEngine.hpp"
# include "cloud.hpp"

# define WINDOW_WIDTH  1720
# define WINDOW_HEIGHT 880
# define FOV 90

using namespace std;
using namespace GE;

typedef struct GameData {
    GE::Window  &window;
    Camera      &camera;
} GameData;

// rendering.cpp
void    initRendering(GE::Window &window, Logger &logger);
void    renderLoop(GameData &gameData);