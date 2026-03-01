#pragma once
#include <string>

namespace Tassathras
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();

		void setData(void* data, uint32_t size);

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		bool operator==(const Texture2D& other) const { return m_rendererID == other.m_rendererID; }

	private:
		unsigned int m_rendererID;
		std::string m_path;
		int m_width;
		int m_height;
		int m_channels;

		// Форматы для OpenGL
		unsigned int m_internalFormat, m_dataFormat;
	};
}