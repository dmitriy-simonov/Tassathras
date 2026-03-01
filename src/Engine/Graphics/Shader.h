#pragma once
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Tassathras
{
    class Shader
    {
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void bind() const;
        void unbind() const;

        // Рассылка Uniform-переменных
        void setInt(const std::string& name, int value);
        void setIntArray(const std::string& name, int* values, uint32_t count); 
        void setFloat(const std::string& name, float value);
        void setFloat3(const std::string& name, const glm::vec3& value);
        void setFloat4(const std::string& name, const glm::vec4& value);
        void setMat4(const std::string& name, const glm::mat4& value);

        inline uint32_t getRendererID() const { return m_rendererID; }
        inline bool isValid() const { return m_rendererID != 0; }

    private:
        uint32_t m_rendererID = 0;
        mutable std::unordered_map<std::string, int> m_UniformLocationCache; 

        int getUniformLocation(const std::string& name) const;
        std::string readFile(const std::string& filepath);
        uint32_t compileShader(uint32_t type, const std::string& source);
    };
}