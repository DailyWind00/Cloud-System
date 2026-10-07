#pragma once

/// System includes
# include <vector>
# include <random>

/// Dependencies
# include <glm/glm.hpp>

/// Defines
#define RANDOM_SEED 0

namespace GE {

	class NoiseGenerator2D {
		public:
			virtual ~NoiseGenerator2D() = 0;

			virtual float sample(glm::vec2 position) const = 0;
			virtual std::vector<float> generateTexture(glm::ivec2 resolution) const = 0;
	};

	class NoiseGenerator3D {
		public:
			virtual ~NoiseGenerator3D() = 0;

			virtual float sample(glm::vec3 position) const = 0;
			virtual std::vector<float> generateTexture(glm::ivec3 resolution) const = 0;
	};
}