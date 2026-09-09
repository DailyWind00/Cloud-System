#pragma once

/// Includes
# include "core/Logger.hpp"

/// System includes
# include <iostream>

/// Dependencies
# include <glad/glad.h>
# include <glfw/glfw3.h>
# include <glm/glm.hpp>


namespace GE {
	// Abstract base class for different types of bounding boxes
	class BoundingBox {
		protected:
			enum class Type {
				SS,
				AABB,
				OBB,
				FDH,
				CH
			};
			Logger	*logger = nullptr;

		public:
			virtual ~BoundingBox() = default;

			/// Public functions

			virtual bool intersects(const BoundingBox& other) const = 0;
			virtual bool contains(const glm::vec3& point) const = 0;

			/// Getters

			virtual Type getType() const = 0;

			/// Setters

			virtual void set(const glm::vec3& min, const glm::vec3& max) = 0;
			virtual void setPosition(const glm::vec3& position) = 0;
			virtual void translate(const glm::vec3& offset) = 0;
			
	};

	/// @brief Axis-Aligned Bounding Box (AABB) class, derived from the BoundingBox base class.
	///
	/// This class represents a 3D bounding box that is aligned with the coordinate axes.
	class AABB : public BoundingBox {
		public:
			glm::vec3 min;
			glm::vec3 max;

			AABB(const glm::vec3& min, const glm::vec3& max, Logger *logger = nullptr);
			~AABB() override = default;

			/// Public functions

			void draw() const;
			bool intersects(const BoundingBox& other) const override;
			inline bool contains(const glm::vec3& point) const override;

			/// Getters

			inline Type getType() const override;

			/// Setters

			void set(const glm::vec3& min, const glm::vec3& max) override;
			void setPosition(const glm::vec3& position) override;
			void translate(const glm::vec3& offset) override;
	};
}