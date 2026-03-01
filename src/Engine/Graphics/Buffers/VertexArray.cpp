#include "VertexArray.h"
#include <glad/glad.h>

namespace Tassathras
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Tassathras::ShaderDataType::Float: return	GL_FLOAT;
		case Tassathras::ShaderDataType::Float2: return GL_FLOAT;
		case Tassathras::ShaderDataType::Float3: return GL_FLOAT;
		case Tassathras::ShaderDataType::Float4: return GL_FLOAT;
		case Tassathras::ShaderDataType::Mat3: return	GL_FLOAT;
		case Tassathras::ShaderDataType::Mat4: return	GL_FLOAT;
		case Tassathras::ShaderDataType::Int: return	GL_INT;
		case Tassathras::ShaderDataType::Int2: return	GL_INT;
		case Tassathras::ShaderDataType::Int3: return	GL_INT;
		case Tassathras::ShaderDataType::Int4: return	GL_INT;
		case Tassathras::ShaderDataType::Bool: return	GL_BOOL;
		}
		return 0;
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_rendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}


	void VertexArray::bind() const
	{
		glBindVertexArray(m_rendererID);
	}
	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		this->bind();
		vertexBuffer->bind();

		const auto& format = vertexBuffer->getFormat();
		uint32_t index = 0;
		for (const auto& element : format)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				format.getStride(),
				(const void*)(uintptr_t)element.Offset);
			index++;
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		bind();
		indexBuffer->bind();
		m_indexBuffers = indexBuffer;
	}
}