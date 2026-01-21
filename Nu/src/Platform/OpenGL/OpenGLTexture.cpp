#include "nupch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Nu {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		NU_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		NU_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);		
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height); // Allocate memory in the GPU to store the image data
		
		// Texture parameters
		// set a few parameters specifically need to deal with what happens when we render our texture on geometry that isn't like one-to-one mapping, so OpenGL will have to shrink or expand the texture its called minification and magnification. others parameters if need it
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR liniarly interpolate the color, when not using bit maps(one reason to use it), also good for image, but not like two colors imaage ex. Chekerboard.png image blurring GL_NEAREST works better.
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_NEAREST be snapping to the nearest pixel, instead of linearly interpolating

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data); // free data from the CPU, because it is already store in GPU, there case when need to retained
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}