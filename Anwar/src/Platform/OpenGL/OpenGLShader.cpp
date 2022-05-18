#include "anwpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Anwar
{
    OpenGLShader::OpenGLShader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
    {
        ANW_PROFILE_FUNCTION();

        std::filesystem::path vertexPath = vertexFilePath;
        std::filesystem::path fragmentPath = fragmentFilePath;
        m_Name = vertexPath.stem().string() + "-" + fragmentPath.stem().string();

        std::string vertexSource = ReadFile(vertexFilePath);
        std::string fragmentSource = ReadFile(fragmentFilePath);
        auto shaderSources = PreProcess(vertexSource, fragmentSource);
        Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name)
    {
        ANW_PROFILE_FUNCTION();

        auto shaderSources = PreProcess(vertexSrc, fragmentSrc);
        Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        ANW_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        ANW_PROFILE_FUNCTION();

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        ANW_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string& name, int* value, uint32_t count)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformIntArray(name, value, count);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformFloat2(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        ANW_PROFILE_FUNCTION();

        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string& name, int* value, uint32_t count)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, value);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    std::string OpenGLShader::ReadFile(const std::string& filePath)
    {
        ANW_PROFILE_FUNCTION();

        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();

            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else
            {
                ANW_CORE_ERROR("Could not open file '{0}'", filePath);
            }
        }
        else
        {
            ANW_CORE_ERROR("Could not open file '{0}'", filePath);
        }
        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& vertexSource, const std::string& fragmentSource)
    {
        ANW_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        shaderSources[GL_VERTEX_SHADER] = vertexSource;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        ANW_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();
        ANW_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
        std::array<GLenum, 2> glShaderIDs{};
        int glShaderIDIndex = 0;

        for (auto&& [type, source] : shaderSources)
        {
            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = (const GLchar*) source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // Compile the shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                ANW_CORE_ERROR("{0}", infoLog.data());
                ANW_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        m_RendererID = program;

        // Link our program
        glLinkProgram(m_RendererID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*) &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_RendererID);

            // Don't leak shaders either.
            for (auto id : glShaderIDs)
            {
                glDeleteShader(id);
            }

            ANW_CORE_ERROR("{0}", infoLog.data());
            ANW_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        for (auto id : glShaderIDs)
        {
            glDetachShader(m_RendererID, id);
        }
    }
}