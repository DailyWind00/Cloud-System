#include "Cloud.hpp"

# pragma region Constructors & Destructors

Cloud::Cloud(glm::vec3 pos, glm::vec3 size, GE::Logger *logger) :
	_volume(pos, size, logger),
	_bufferGL(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(glm::vec3) * 2, nullptr)
{
	this->logger = logger;
}

Cloud::~Cloud()
{

}

# pragma endregion

# pragma region Public functions

void	Cloud::draw()
{
	_volume.draw();
}

# pragma endregion