#pragma once

# include "Objects/BoundingBox.hpp"
# include "Objects/Camera.hpp"
# include "OpenGL/BufferGL.hpp"
# include "OpenGL/Shader.hpp"
# include "OpenGL/Window.hpp"
# include "OpenGL/GLTexture.hpp"
# include "Utils/Noises/WorleyNoise.hpp"

/// @brief Set the quality of the clouds, higher quality can lower performances.
enum class CloudQuality {
    Disabled,
    Low,
    Medium,
    High,
    Ultra,
    Cinematic
};

/**
 * @brief The Cloud class generate a Axis-Aligned Bounding Box (AABB) that is used to render volumetric clouds inside it on the GPU.
 */
class Cloud {
	public:
		Cloud(
			glm::vec3	min,
			glm::vec3	max,
			GE::Logger *logger = nullptr
		);
		~Cloud();

		/// Public functions

		void	draw(GE::Shader &shader, GE::Window &window, GE::Camera &camera);

	private:
		GE::AABB			_volume;
		GLuint				_VAO;
		GE::WorleyNoise3D	_worley;
		GE::GLTexture3D		_worleyTexture;

		GE::Logger	*logger = nullptr;
};