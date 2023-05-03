#ifndef RVL_RECTANGLE_HPP
#define RVL_RECTANGLE_HPP

#include <Core/Core.hpp>
#include <API/Property.hpp>
#include <Rendering/Renderer/Transform.hpp>

namespace rvl
{
    class GLVertexBuffer;
    class GLIndexBuffer;
    class GLVertexArray;
    class GLShaderProgram;

    class Rectangle
    {
    public:
        static Ref<Rectangle> Create();
        static Ref<Rectangle> Create(const Transform& transform, const glm::vec3& color);
        static Ref<Rectangle> Create(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color = {1.f, 1.f, 1.f});

        Rectangle();
        Rectangle(const Transform& transform, const glm::vec3& color);
        Rectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color = {1.f, 1.f, 1.f});
        ~Rectangle();

        void Draw();

        Property<Transform> transform = {&_transform};

        glm::vec3 GetColor() const;
        void SetColor(const glm::vec3& color);

    private:
        Transform _transform;

        glm::vec3 _color;
    };
}

#endif
