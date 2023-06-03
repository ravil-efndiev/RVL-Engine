#include "GLBuffer.hpp"

namespace Rvl
{
    /// Vertex buffer

    GLVertexBuffer::GLVertexBuffer(size_t size, int components, bool normalized) : _normalized(normalized)
    {
        _verticiesCount = components;
        CreateBuffer(size);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<float>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 1);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec2>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 2);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec3>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 3);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec4>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 4);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &_bufferId);
    }

    void GLVertexBuffer::CreateBuffer(size_t size)
    {
        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW );
    }

    template <class T>
    inline void GLVertexBuffer::CreateBuffer(const std::vector<T> &verticies, int verticiesCount)
    {
        _verticiesCount = verticiesCount;

        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(T), verticies.data(), GL_STATIC_DRAW);
    }

    void GLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    }

    void GLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::SetData(void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    int GLVertexBuffer::GetVerticiesCount() const
    {
        return _verticiesCount;
    }

    bool GLVertexBuffer::GetNormalized() const
    {
        return _normalized;
    }

    GLuint GLVertexBuffer::GetId() const
    {
        return _bufferId;
    }

    /// Index buffer

    GLIndexBuffer::GLIndexBuffer(const std::vector<uint32_t>& indicies)
    {
        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);   
        _indiciesCount = indicies.size();
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &_bufferId);
    }

    void GLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    }

    void GLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int GLIndexBuffer::GetIndiciesCount()
    {
        return _indiciesCount;
    }
}
