#ifndef RVL_GLTEXTURE_HPP
#define RVL_GLTEXTURE_HPP

#include <Rvlpch.hpp>

namespace rvl
{
    class GLTexture
    {
    public:
        GLTexture();
        GLTexture(uint32_t width, uint32_t height);
        GLTexture(const std::string& path);
        GLTexture(const GLTexture& tex) = delete;
        ~GLTexture();

        void LoadTexture(const std::string& path);
        void SetData(uint8_t* data, size_t size);

        void Bind() const;
        void Unbind() const;

        int GetWidth() const;
        int GetHeight() const;

    private:
        GLuint _textureId;
        int _width, _height, _channels;        
        unsigned char* _textureData;

    };
}

#endif
