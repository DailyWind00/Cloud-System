#include "Cloud.hpp"

# pragma region Constructors & Destructors

Cloud::Cloud(glm::vec3 min, glm::vec3 max, GE::Logger *logger) :
	_volume(min, max, logger)
{
	this->logger = logger;
	glGenVertexArrays(1, &_VAO);
}

Cloud::~Cloud()
{
	glDeleteVertexArrays(1, &_VAO);
}

# pragma endregion

# pragma region Public functions

/// @brief Draw the cloud on the screen.
///
/// The cloud is rendered on a fullscreen pass, using the AABB to filter the raycasts.
///
/// @param shader The shader of the cloud.
/// @param camera The camera used for the raymarching.
void	Cloud::draw(GE::Shader &shader, GE::Camera &camera)
{
	shader.use();
	shader.setUniform("uCamPos", camera.getCameraInfo().position);
	shader.setUniform("uView", camera.getViewMatrix());
	shader.setUniform("uProj", camera.getProjectionMatrix());
	shader.setUniform("uCloudMin", _volume.min);
	shader.setUniform("uCloudMax", _volume.max);

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

# pragma endregion