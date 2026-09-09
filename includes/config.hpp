#pragma once

# include "GameEngine.hpp"
# include "Cloud.hpp"

# define WINDOW_WIDTH  1720
# define WINDOW_HEIGHT 880
# define FOV 90
# define CAMERA_SPEED 0.01f
# define CAMERA_SENSITIVITY 0.015f

using namespace std;
using namespace GE;

typedef struct GameData {
    GE::Window  &window;
    Camera      &camera;
	Shader		shaders[3];
	SkyBox		&skybox;
	Cloud		&test_cloud;
} GameData;

// rendering.cpp
void    initRendering(GE::Window &window, Logger &logger);
void    renderLoop(GameData &gameData);

// events.cpp
void	handleEvents(GameData &gameData);