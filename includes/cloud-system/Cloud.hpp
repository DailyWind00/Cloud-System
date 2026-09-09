#pragma once

# include "Objects/BoundingBox.hpp"
# include "OpenGL/BufferGL.hpp"

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
			glm::vec3	pos,
			glm::vec3	size,
			GE::Logger *logger = nullptr
		);
		~Cloud();

		/// Public functions

		void	draw();

	private:
		GE::AABB		_volume;
		GE::BufferGL	_bufferGL;

		GE::Logger	*logger = nullptr;
};