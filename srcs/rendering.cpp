#include "config.hpp"

void    initRendering(GE::Window &window, Logger &logger)
{
    // Mouse Parameters
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	// glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSetCursorPos(*window, (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);

    // OpenGL Parameters
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Systems Initialization
    Camera camera(
		(CameraInfo){{0, 0, 0}, {0, 0, 1}, {0, 1, 0}},
		(ProjectionInfo){FOV, 0.1f, 10000.0f, {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}, {0.0f, 0.0f}},
        Camera::ProjectionType::PERSPECTIVE,
        &logger
	);

    GameData gameData = {
		window,
		camera
	};
    
    window.mainLoop(renderLoop, gameData);
}

void    renderLoop(GameData &gameData) {
	(void)gameData;
}
