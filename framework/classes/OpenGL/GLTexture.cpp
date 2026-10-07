#include "GLTexture.hpp"

namespace GE {

# pragma region GLTexture2D

    GLTexture2D::GLTexture2D(
        glm::ivec2 resolution,
        GLenum internalFormat,
        GLenum format,
        GLenum type,
        GLenum minFilter,
        GLenum magFilter,
        GLenum wrapMode,
        const void* data
    ) :
        _resolution(resolution),
        _internalFormat(internalFormat),
        _format(format),
        _type(type)
    {
        glGenTextures(1, &_id);

        bind();

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            minFilter
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            magFilter
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            wrapMode
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            wrapMode
        );

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            _internalFormat,
            _resolution.x,
            _resolution.y,
            0,
            _format,
            _type,
            data
        );

        unbind();
    }

    GLTexture2D::~GLTexture2D()
    {
        glDeleteTextures(1, &_id);
    }

	/// @brief Bind the buffer
    void GLTexture2D::bind()
    {
        glBindTexture(GL_TEXTURE_2D, _id);
    }

	/// @brief Unbind the buffer
    void GLTexture2D::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

	/// @brief Update the buffer data
	/// @param data The new data to update
    void GLTexture2D::updateData(const void* data)
    {
        bind();

        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            _resolution.x,
            _resolution.y,
            _format,
            _type,
            data
        );

        unbind();
    }

    /// @brief Get the OpenGL texture ID
    /// @return The OpenGL texture ID
    const GLuint& GLTexture2D::getID() const {
        return _id;
    }

    /// @brief Get the resolution of the 3D texture
    /// @return The resolution of the 3D texture as a glm::ivec3
    const glm::ivec2& GLTexture2D::getResolution() const {
        return _resolution;
    }

    /// @brief Get the internal format of the texture (e.g., GL_R32F, GL_RGBA8)
    /// @return The internal format of the texture
    const GLenum& GLTexture2D::getInternalFormat() const {
        return _internalFormat;
    }

    /// @brief Get the format of the texture data (e.g., GL_RGB, GL_RGBA)
    /// @return The format of the texture data
    const GLenum& GLTexture2D::getFormat() const {
        return _format;
    }

	/// @brief Get the type of the texture data (e.g., GL_FLOAT, GL_UNSIGNED_BYTE)
	/// @return The type of the texture data
    const GLenum& GLTexture2D::getType() const {
        return _type;
    }

# pragma endregion

# pragma region GLTexture3D

	GLTexture3D::GLTexture3D(
        glm::ivec3 resolution,
        GLenum internalFormat,
        GLenum format,
        GLenum type,
        GLenum minFilter,
        GLenum magFilter,
        GLenum wrapMode,
        const void* data
    ) :
        _resolution(resolution),
        _internalFormat(internalFormat),
        _format(format),
        _type(type)
    {
        glGenTextures(1, &_id);

        bind();

        glTexParameteri(
            GL_TEXTURE_3D,
            GL_TEXTURE_MIN_FILTER,
            minFilter
        );
        glTexParameteri(
            GL_TEXTURE_3D,
            GL_TEXTURE_MAG_FILTER,
            magFilter
        );
        glTexParameteri(
            GL_TEXTURE_3D,
            GL_TEXTURE_WRAP_S,
            wrapMode
        );
        glTexParameteri(
            GL_TEXTURE_3D,
            GL_TEXTURE_WRAP_T,
            wrapMode
        );
        glTexParameteri(
            GL_TEXTURE_3D,
            GL_TEXTURE_WRAP_R,
            wrapMode
        );

        glTexImage3D(
            GL_TEXTURE_3D,
            0,
            _internalFormat,
            _resolution.x,
            _resolution.y,
            _resolution.z,
            0,
            _format,
            _type,
            data
        );

        unbind();
    }


    GLTexture3D::~GLTexture3D()
	{
        glDeleteTextures(1, &_id);
    }

	/// @brief Bind the buffer
    void GLTexture3D::bind() {
        glBindTexture(GL_TEXTURE_3D, _id);
    }

	/// @brief Unbind the buffer
    void GLTexture3D::unbind() {
        glBindTexture(GL_TEXTURE_3D, 0);
    }

	/// @brief Update the buffer data
	/// @param data The new data to update
    void GLTexture3D::updateData(const void* data)
    {
        bind();

        glTexSubImage3D(
            GL_TEXTURE_3D,
            0,
            0, 0, 0,
            _resolution.x,
            _resolution.y,
            _resolution.z,
            _format,
            _type,
            data
        );

        unbind();
    }

    /// @brief Get the OpenGL texture ID
    /// @return The OpenGL texture ID
    const GLuint& GLTexture3D::getID() const {
        return _id;
    }

    /// @brief Get the resolution of the 3D texture
    /// @return The resolution of the 3D texture as a glm::ivec3
    const glm::ivec3& GLTexture3D::getResolution() const {
        return _resolution;
    }

    /// @brief Get the internal format of the texture (e.g., GL_R32F, GL_RGBA8)
    /// @return The internal format of the texture
    const GLenum& GLTexture3D::getInternalFormat() const {
        return _internalFormat;
    }

    /// @brief Get the format of the texture data (e.g., GL_RGB, GL_RGBA)
    /// @return The format of the texture data
    const GLenum& GLTexture3D::getFormat() const {
        return _format;
    }

	/// @brief Get the type of the texture data (e.g., GL_FLOAT, GL_UNSIGNED_BYTE)
	/// @return The type of the texture data
	const GLenum& GLTexture3D::getType() const {
		return _type;
	}

	# pragma endregion

}