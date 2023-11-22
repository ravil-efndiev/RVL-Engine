#pragma once
#include <Core/Core.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>

namespace Rvl
{
    class GLShaderProgram;
    struct MaterialComponent
    {
        MaterialComponent() = default;
        MaterialComponent(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        MaterialComponent(glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        ~MaterialComponent() {}

        bool ProcessLightSources = true;
        float Shininess;
        glm::vec3 Diffuse;
        glm::vec3 Ambient;
        glm::vec3 Specular;
        Ref<GLShaderProgram> Shader;

        template <class T> 
        inline void SetUniform(const std::string& name, const T& value)
        {
            Shader->Bind();
            if constexpr (std::is_same<T, float>()) { Shader->SetUniformFloat(name, value); } 
            if constexpr (std::is_same<T, int>()) { Shader->SetUniformInt(name, value); } 
            if constexpr (std::is_same<T, glm::vec2>()) { Shader->SetUniformVec2(name, value); }
            if constexpr (std::is_same<T, glm::vec3>()) { Shader->SetUniformVec3(name, value); }
            if constexpr (std::is_same<T, glm::vec4>()) { Shader->SetUniformVec4(name, value); }
            Shader->Unbind();
        }
    };
}
