#pragma once
#include <cstdint>

namespace Tassathras
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Tassathras::ShaderDataType::None:
		case Tassathras::ShaderDataType::Float:  return 4;
		case Tassathras::ShaderDataType::Float2: return 4 * 2;
		case Tassathras::ShaderDataType::Float3: return 4 * 3;
		case Tassathras::ShaderDataType::Float4: return 4 * 4;
		case Tassathras::ShaderDataType::Mat3:	 return 4 * 3 * 3;
		case Tassathras::ShaderDataType::Mat4:   return 4 * 4 * 4;
		case Tassathras::ShaderDataType::Int:	 return 4;
		case Tassathras::ShaderDataType::Int2:	 return 4 * 2;
		case Tassathras::ShaderDataType::Int3:   return 4 * 3;
		case Tassathras::ShaderDataType::Int4:   return 4 * 4;
		case Tassathras::ShaderDataType::Bool:   return 1;
		}
		return 0;
	}
}