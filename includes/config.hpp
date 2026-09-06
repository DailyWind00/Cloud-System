#pragma once

# include "GameEngine.hpp"
# include "cloud.hpp"

# define WINDOW_WIDTH  800
# define WINDOW_HEIGHT 800
# define FOV 90

using namespace std;
using namespace GE;

typedef struct GameData {
    GE::Window  &window;
    Camera      &camera;
} GameData;

// rendering.cpp
void    initRendering(GE::Window &window, Logger &logger);
void    renderLoop();