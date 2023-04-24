#include "Sprite.hpp"
#include <Rvlglpch.hpp>

#include <stb_image.h>
#include <Core/Platform.hpp>

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

#include "Rendering/Renderer/Renderer.hpp"

namespace rvl
{
    int Sprite::_unit = 0;

    Sprite::Sprite() : Entity(0.f, 0.f) {}

    Sprite::Sprite(const Vector2f& position) : Entity(position) {}

    Sprite::Sprite(float x, float y) : Entity(x, y) {}   

    Sprite::~Sprite() {}

    void Sprite::LoadTexture(const std::string &filename)
    {

        _texture = std::make_unique<GLTexture>(filename);
        GenerateMesh();
        _unit += 1;
    }

    void Sprite::Draw()
    {
        _texture->Bind(--_unit);
        Renderer::SubmitGeometry(*_vao, *_shaderProgram);
        _texture->Unbind();
    }

    void Sprite::GenerateMesh()
    {
        float ratio = (float)_texture->GetWidth() / (float)_texture->GetHeight();
        RVL_LOG(ratio);

        _vao = std::make_unique<GLVertexArray>();

        _positionVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>(
            {
                {-ratio + _position.X(), -1 + _position.Y(), 0.0f},
                {ratio + _position.X(), -1  + _position.Y(), 0.0f},
                {ratio + _position.X(), 1  + _position.Y(), 0.0f},
                {-ratio  + _position.X(), 1 + _position.Y(), 0.0f},
            }
        ));

        glm::vec3 glmColor = glm::vec3(1.f, 1.f, 1.f);

        _colorVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>(
            {glmColor, glmColor, glmColor, glmColor}
        ));

        _textureCoordsVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec2>(
            {
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f}
            }
        ));

        _indicies = std::make_shared<GLIndexBuffer>(std::vector<uint32_t>({0, 1, 2, 2, 3, 0}));

        _vao->AddVertexBuffer(_positionVbo);
        _vao->AddVertexBuffer(_colorVbo);
        _vao->AddVertexBuffer(_textureCoordsVbo);
        _vao->AddIndexBuffer(_indicies);

        _shaderProgram = std::make_unique<GLShaderProgram>("../RVL/res/shaders/textured.vert", "../RVL/res/shaders/textured.frag");
        _shaderProgram->BindAttribute(RVL_POSITION_LOCATION, "position");
        _shaderProgram->BindAttribute(RVL_COLOR_LOCATION,    "color");
        _shaderProgram->BindAttribute(RVL_TEXTURE_LOCATION,  "coords");
        _shaderProgram->Link();

        _shaderProgram->SetUniform("Texture", _unit);
    }

    void Sprite::ResetPosition()
    {
        GLVertexBuffer newPos
        (
            {
                {-1  + _position.X(), -1 + _position.Y(), 0.0f},
                {1 + _position.X(), -1  + _position.Y(), 0.0f},
                {1 + _position.X(), 1  + _position.Y(), 0.0f},
                {-1  + _position.X(), 1 + _position.Y(), 0.0f},
            }
        );

        _vao->ResetVertexBuffer(RVL_POSITION_LOCATION, newPos);
    }
}
