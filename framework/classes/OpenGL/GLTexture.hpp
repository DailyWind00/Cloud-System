#pragma once

/// System includes
# include <iostream>
# include <vector>

/// Dependencies
# include <glad/glad.h>
# include <glm/glm.hpp>

namespace GE {
	/// @brief This class is a simple wrapper around OpenGL textures 2D.
	///
	/// It allows to create, bind, unbind, update and delete 2D textures.
	///
	/// @note As this class may be frequently used, it is designed to be as lightweight as possible and have no logging integrated.
    class GLTexture2D {

        public:

            GLTexture2D(
                glm::ivec2 resolution,
                GLenum internalFormat = GL_RGBA8,
                GLenum format = GL_RGBA,
                GLenum type = GL_UNSIGNED_BYTE,
                GLenum minFilter = GL_LINEAR,
                GLenum magFilter = GL_LINEAR,
                GLenum wrapMode = GL_REPEAT,
                const void* data = nullptr
            );

            ~GLTexture2D();

            GLTexture2D(const GLTexture2D&) = delete;
            GLTexture2D& operator=(const GLTexture2D&) = delete;

            /// Public functions

            void    bind();
            void    unbind();

            void    updateData(const void* data);

            /// Getters

            const GLuint&       getID() const;
            const glm::ivec2&   getResolution() const;
            const GLenum&       getInternalFormat() const;
            const GLenum&       getFormat() const;
            const GLenum&       getType() const;

        private:

            GLuint      _id;
            glm::ivec2  _resolution;

            GLenum      _internalFormat;
            GLenum      _format;
            GLenum      _type;
    };


	
	/// @brief This class is a simple wrapper around OpenGL textures 3D.
	///
	/// It allows to create, bind, unbind, update and delete 3D textures.
	///
	/// @note As this class may be frequently used, it is designed to be as lightweight as possible and have no logging integrated.
	class GLTexture3D {
		public:
			GLTexture3D(
				glm::ivec3 resolution,
				GLenum internalFormat = GL_R32F,
				GLenum format = GL_RED,
				GLenum type = GL_FLOAT,
				GLenum minFilter = GL_LINEAR,
				GLenum magFilter = GL_LINEAR,
				GLenum wrapMode = GL_REPEAT,
				const void* data = nullptr	
			);
			~GLTexture3D();

			/// Public functions

			void bind();
			void unbind();

			void updateData(const void* data);

			/// Getters

			const GLuint&       getID() const;
			const glm::ivec3&   getResolution() const;
			const GLenum&       getInternalFormat() const;
			const GLenum&       getFormat() const;
			const GLenum&       getType() const;

		private:

			GLuint      _id;
			glm::ivec3  _resolution;

			GLenum      _internalFormat;
			GLenum      _format;
			GLenum      _type;
	};
}