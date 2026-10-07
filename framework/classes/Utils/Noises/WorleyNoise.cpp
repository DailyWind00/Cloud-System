#include "WorleyNoise.hpp"

namespace GE {
	
	WorleyNoise3D::WorleyNoise3D(
		glm::ivec3 resolution,
		float cellSize,
		bool loop,
    	uint32_t seed
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
		if (_loop) // Modulo back in the resolution if outside of the resolution and looping
		{
			const glm::vec3 size = glm::vec3(_resolution) * _cellSize;

			position = glm::mod(position, size);
			position = glm::mod(position + size, size); // Negatives
		}
		if (!_loop) // Return 0 if outside of the resolution and not looping
		{
			const glm::vec3 size = glm::vec3(_resolution) * _cellSize;

			if (glm::any(glm::lessThan(position, glm::vec3(0.0f))) ||
				glm::any(glm::greaterThanEqual(position, size)))
			{
				return 0.0f;
			}
		}
		
		glm::ivec3 cell = glm::ivec3(glm::floor(position / _cellSize));

		float minDistance = std::numeric_limits<float>::max();

		for (int z = -1; z <= 1; ++z)
		{
			for (int y = -1; y <= 1; ++y)
			{
				for (int x = -1; x <= 1; ++x)
				{
					glm::ivec3 neighbor = cell + glm::ivec3(x, y, z);

					if (_loop)
					{
						neighbor.x = ((neighbor.x % _resolution.x) + _resolution.x) % _resolution.x;
						neighbor.y = ((neighbor.y % _resolution.y) + _resolution.y) % _resolution.y;
						neighbor.z = ((neighbor.z % _resolution.z) + _resolution.z) % _resolution.z;
					}
					else
					{
						if (
							neighbor.x < 0 || neighbor.x >= _resolution.x ||
							neighbor.y < 0 || neighbor.y >= _resolution.y ||
							neighbor.z < 0 || neighbor.z >= _resolution.z
						)
							continue;
					}

					const int index =
						neighbor.x +
						neighbor.y * _resolution.x +
						neighbor.z * _resolution.x * _resolution.y;

					const glm::vec3& featurePoint = _featurePoints[index];

					const float distance = glm::distance(
						position,
						featurePoint
					);

					minDistance = std::min(minDistance, distance);
				}
			}
		}

		return minDistance / _cellSize;
	}

	std::vector<float> WorleyNoise3D::generateTexture() const
	{
		const int voxelCount =
			_resolution.x *
			_resolution.y *
			_resolution.z;

		std::vector<float> texture(voxelCount);

		for (int z = 0; z < _resolution.z; ++z)
		{
			for (int y = 0; y < _resolution.y; ++y)
			{
				for (int x = 0; x < _resolution.x; ++x)
				{
					const glm::vec3 position(
						(x + 0.5f) * _cellSize,
						(y + 0.5f) * _cellSize,
						(z + 0.5f) * _cellSize
					);

					const int index =
						x +
						y * _resolution.x +
						z * _resolution.x * _resolution.y;

					texture[index] = sample(position);
				}
			}
		}

		return texture;
	}
}