#include "WorleyNoise.hpp"

namespace GE {
	
	WorleyNoise3D::WorleyNoise3D(
		glm::ivec3 resolution,
		float cellSize,
		bool loop = true,
    	uint32_t seed = RANDOM_SEED
	) : 
		_resolution(resolution),
		_cellSize(cellSize),
		_loop(loop)
	{
		const int cellCount = resolution.x * resolution.y * resolution.z;

		_featurePoints.resize(cellCount);

		std::random_device rd;
		std::mt19937 rng(seed ? seed : rd());

    	std::uniform_real_distribution<float> random(0.0f, 1.0f);

		for (int z = 0; z < resolution.z; ++z)
		{
			for (int y = 0; y < resolution.y; ++y)
			{
				for (int x = 0; x < resolution.x; ++x)
				{
					glm::vec3 point(
						(x + random(rng)) * _cellSize,
						(y + random(rng)) * _cellSize,
						(z + random(rng)) * _cellSize
					);

					int index =
						x +
						y * resolution.x +
						z * resolution.x * resolution.y;

					_featurePoints[index] = point;
				}
			}
		}
	};

	float WorleyNoise3D::sample(glm::vec3 position) const
	{

	}
}