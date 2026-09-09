#include "config.hpp"

// Check if a key is pressed once
// Handle multiple keys
// Returns true a single time if the key has been pressed, false otherwise
static inline bool keyPressedOnce(GLFWwindow *window, int key) {
	static unordered_map<int, bool> pressed;

	if (glfwGetKey(window, key) == GLFW_PRESS && !pressed[key]) {
		pressed[key] = true;
		return true;
	}
	else if (glfwGetKey(window, key) == GLFW_RELEASE)
		pressed[key] = false;

	return false;
}

// Check if a mouse button is pressed once
// Handle multiple buttons
// Returns true a single time if the button has been pressed, false otherwise
static inline bool MouseButtonPressedOnce(GLFWwindow *window, int button) {
	static unordered_map<int, bool> pressed;

	if (glfwGetMouseButton(window, button) == GLFW_PRESS && !pressed[button]) {
		pressed[button] = true;
		return true;
	}
	else if (glfwGetMouseButton(window, button) == GLFW_RELEASE)
		pressed[button] = false;

	return false;
}

static void	cameraMovements(GameData &gameData)
{
	const float camSpeed = CAMERA_SPEED * gameData.window.getFrameTime();

	CameraInfo	cameraInfo = gameData.camera.getCameraInfo();
	const glm::vec3	cameraFront = cameraInfo.lookAt - cameraInfo.position;
	const glm::vec3	cameraRight = normalize(cross(cameraFront, cameraInfo.up));
	const glm::vec3 cameraUp = cameraInfo.up;

	glm::vec3 move = glm::vec3(0);
	if (glfwGetKey(gameData.window, GLFW_KEY_W) == GLFW_PRESS) move += cameraFront;
	if (glfwGetKey(gameData.window, GLFW_KEY_S) == GLFW_PRESS) move -= cameraFront;
	if (glfwGetKey(gameData.window, GLFW_KEY_A) == GLFW_PRESS) move -= cameraRight;
	if (glfwGetKey(gameData.window, GLFW_KEY_D) == GLFW_PRESS) move += cameraRight;
	if (glfwGetKey(gameData.window, GLFW_KEY_SPACE) == GLFW_PRESS) move += cameraUp;
	if (glfwGetKey(gameData.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) move -= cameraUp;
	if (length(move) > 1.0f)
		move = normalize(move);

	glm::vec3 translation = move * camSpeed;

	gameData.camera.addToPosition(translation);

	cameraInfo = gameData.camera.getCameraInfo(); // Refresh camera info after potential movement

	double mouseX, mouseY;
	glfwGetCursorPos(gameData.window, &mouseX, &mouseY);

	static glm::vec2	angles = glm::vec2(0, 0);
	angles.x += (mouseX - ((float)WINDOW_WIDTH  / 2)) * CAMERA_SENSITIVITY * gameData.window.getFrameTime();
	angles.y -= (mouseY - ((float)WINDOW_HEIGHT / 2)) * CAMERA_SENSITIVITY * gameData.window.getFrameTime();
	angles.y = glm::clamp(angles.y, -89.0f, 89.0f);

	glm::vec3	cameraDir = glm::vec3{
		cos(glm::radians(angles.x)) * cos(glm::radians(angles.y)),
		sin(glm::radians(angles.y)),
		sin(glm::radians(angles.x)) * cos(glm::radians(angles.y))
	};

	glfwSetCursorPos(gameData.window, (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);

	gameData.camera.setLookAt(cameraInfo.position + cameraDir);
}

void    handleEvents(GameData &gameData)
{
	if (keyPressedOnce(gameData.window, GLFW_KEY_ESCAPE))
		gameData.window.setShouldClose(true);

	// Temporary
	gameData.shaders[2].setUniform("view", gameData.camera.getViewMatrix());
	gameData.shaders[2].setUniform("projection", gameData.camera.getProjectionMatrix());
	gameData.shaders[2].setUniform("gPosition", 0);
	gameData.shaders[2].setUniform("gNormal", 1);
	gameData.shaders[2].setUniform("gColor", 2);

	cameraMovements(gameData);
}