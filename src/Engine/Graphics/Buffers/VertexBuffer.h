#pragma once
#include "VertexFormat.h"
#include <cstdint>

namespace Tassathras
{


	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size); //fix size vbo
		VertexBuffer(const void* data, uint32_t size);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void bind() const;
		void unbind() const;

		void setData(const void* data, uint32_t size, uint32_t offset = 0);

		void setFormat(const VertexFormat& format) { m_format = format; }
		const VertexFormat& getFormat() const { return m_format; }
	private:
		uint32_t m_rendererID;
		VertexFormat m_format;

	};
}