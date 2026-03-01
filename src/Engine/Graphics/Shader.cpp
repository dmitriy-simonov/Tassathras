#include "Shader.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>

namespace Tassathras
{
    Shader::Shader(const std::string& filepath)
    {
        std::string source = readFile(filepath);
        if (source.empty()) return;

        // Разделение на Vertex и Fragment шейдеры
        std::string vertexSource, fragmentSource;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);

        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);

            if (type == "vertex")
                vertexSource = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
            else if (type == "fragment")
                fragmentSource = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexSource);
        uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

        if (vs == 0 || fs == 0) return;

        m_rendererID = glCreateProgram();
        glAttachShader(m_rendererID, vs);
        glAttachShader(m_rendererID, fs);

        glBindAttribLocation(m_rendererID, 0, "a_Position");
        glBindAttribLocation(m_rendererID, 1, "a_TexCoord");
        glBindAttribLocation(m_rendererID, 2, "a_Color");
        glBindAttribLocation(m_rendererID, 3, "a_TexIndex");

        glLinkProgram(m_rendererID);

        int isLinked = 0;
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, infoLog.data());
            TS_CORE_ERROR("Shader link error ({0}): {1}", filepath, infoLog.data());
            glDeleteProgram(m_rendererID);
            m_rendererID = 0;
        }

        glDetachShader(m_rendererID, vs);
        glDetachShader(m_rendererID, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader() { if (m_rendererID) glDeleteProgram(m_rendererID); }

    void Shader::bind() const { glUseProgram(m_rendererID); }
    void Shader::unbind() const { glUseProgram(0); }


    int Shader::getUniformLocation(const std::string& name) const
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        int location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
            TS_CORE_WARN("Uniform '{0}' not found in shader!", name);

        m_UniformLocationCache[name] = location;
        return location;
    }

    void Shader::setInt(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setIntArray(const std::string& name, int* values, uint32_t count)
    {
        glUniform1iv(getUniformLocation(name), count, values);
    }

    void Shader::setFloat(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }


    std::string Shader::readFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else {
            TS_CORE_ERROR("Could not open file '{0}'", filepath);
        }
        return result;
    }

    uint32_t Shader::compileShader(uint32_t type, const std::string& source)
    {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message(length);
            glGetShaderInfoLog(id, length, &length, message.data());
            TS_CORE_ERROR("Failed to compile {0} shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            TS_CORE_ERROR(message.data());
            glDeleteShader(id);
            return 0;
        }
        return id;
    }
}