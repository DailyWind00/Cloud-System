#include "config.hpp"

void    initRendering(GE::Window &window, Logger &logger)
{
    // Mouse Parameters
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);

    // OpenGL Parameters
    glClearColor(
		135 / 255.0f,
		206 / 255.0f,
		235 / 255.0f,
		1.0f
	);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Systems Initialization
    Camera camera(
		(CameraInfo){{0, 0, -1}, {0, 0, 1}, {0, 1, 0}},
		(ProjectionInfo){FOV, 0.1f, 10000.0f, {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}, {0.0f, 0.0f}},
        Camera::ProjectionType::PERSPECTIVE,
        &logger
	);
	Shader	cloud_shader("shaders/cloud.vert", "shaders/cloud.frag", &logger);
	Shader	skybox_shader("framework/shaders/Skybox-shaderonly.vert", "framework/shaders/Skybox-shaderonly.frag", &logger);
	Shader	AABB_shader("framework/shaders/AABB-debug.vert", "framework/shaders/AABB-debug.frag", &logger);

	SkyBox	skybox(&logger);

	Cloud	test({-0.5, -0.5, -0.5,}, {0.5, 0.5, 0.5,}, &logger);

    GameData gameData = {
		window,
		camera,
		{cloud_shader, skybox_shader, AABB_shader},
		skybox,
		test
	};
    
    window.mainLoop(renderLoop, gameData);
}

void    renderLoop(GameData &gameData)
{
	gameData.test_cloud.draw(gameData.shaders[0], gameData.window, gameData.camera);

	handleEvents(gameData);
}
