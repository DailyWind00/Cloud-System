#include "../NoiseGenerator.hpp"

namespace GE {
	/**
	 * @brief A 3D Worley noise generator.
	 * 
	 * Worley noise, also known as cellular noise, is a type of procedural noise that
	 * generates patterns based on the distance to the nearest feature point in a grid.
	 */
	class WorleyNoise3D : public NoiseGenerator3D {
		public:
			WorleyNoise3D(
				glm::ivec3 resolution,
				float cellSize,
				bool loop = true,
				uint32_t seed = RANDOM_SEED
			);

			float sample(glm::vec3 position) const override;
			std::vector<float> generateTexture(glm::ivec3 resolution) const override;

		private:
			glm::ivec3	_resolution;
			float		_cellSize;
			bool		_loop;

			std::vector<glm::vec3> _featurePoints;
	};
}