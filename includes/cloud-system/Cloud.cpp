#include "Cloud.hpp"

# pragma region Constructors & Destructors

Cloud::Cloud(glm::vec3 min, glm::vec3 max, GE::Logger *logger) :
	_volume(min, max, logger),
	_worley(
		glm::ivec3(32, 32, 32),
		1.0f
	),
	_worleyTexture(
		_worley.getResolution(),
		GL_R32F,
		GL_RED,
		GL_FLOAT,
		GL_LINEAR,
		GL_LINEAR,
		GL_REPEAT,
		_worley.generateTexture().data()
	)
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
/// @param window The window used.
/// @param camera The camera used for the raymarching.
void	Cloud::draw(GE::Shader &shader, GE::Window &window, GE::Camera &camera)
{
	shader.use();
	shader.setUniform("uCamPos", camera.getCameraInfo().position);
	shader.setUniform("uInvView", glm::inverse(camera.getViewMatrix()));
	shader.setUniform("uInvProj", glm::inverse(camera.getProjectionMatrix()));
	shader.setUniform("uScreenSize", (glm::vec2)window.getScreenSize());
	shader.setUniform("uCloudMin", _volume.min);
	shader.setUniform("uCloudMax", _volume.max);

	glBindVertexArray(_VAO);
	glActiveTexture(GL_TEXTURE1);
	_worleyTexture.bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	_worleyTexture.unbind();
	glBindVertexArray(0);
}

# pragma endregion