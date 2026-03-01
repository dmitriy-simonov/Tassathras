#include "Texture.h"
#include "Core/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

namespace Tassathras
{
	Texture2D::Texture2D(const std::string& path)
		: m_path(path), m_internalFormat(GL_RGBA8), m_dataFormat(GL_RGBA)
	{
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);

		if (data)
		{
			glGenTextures(1, &m_rendererID);
			glBindTexture(GL_TEXTURE_2D, m_rendererID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else {
			TS_CORE_ERROR("Failed to load texture at: {0}", path);
		}
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height)
		: m_width(width), m_height(height), m_internalFormat(GL_RGBA8), m_dataFormat(GL_RGBA)
	{
		glGenTextures(1, &m_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_rendererID);
	}

	void Texture2D::setData(void* data, uint32_t size)
	{
		uint32_t bpp = (m_dataFormat == GL_RGBA) ? 4 : 3;
		if (size != m_width * m_height * bpp) {
			TS_CORE_ERROR("Data must be entire texture!");
			return;
		}

		glBindTexture(GL_TEXTURE_2D, m_rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_rendererID);
	}

	void Texture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}