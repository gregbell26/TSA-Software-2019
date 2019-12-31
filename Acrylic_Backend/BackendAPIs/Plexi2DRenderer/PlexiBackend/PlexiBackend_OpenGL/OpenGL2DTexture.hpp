#ifndef OPENGL_2D_TEXTURE_HPP
#define OPENGL_2D_TEXTURE_HPP

#if defined(LINUX)

#include <cstring>

#endif
class OpenGL2DTexture: public Plexi2DTexture {
public:
    explicit OpenGL2DTexture(const uint32_t& providedId) :
        id(providedId), height(0), width(0), glId(0), dataFormat(0), internalFormat(0)
    {};
    ~OpenGL2DTexture() override;

    void createTexture(void* data, uint32_t size, uint32_t height, uint32_t width, uint32_t channelCount) override;

    void bind(uint32_t textureSlot) override; // We can only have one texture slot in openGL 4.1 so we are ignoring this

    void unbind() override;

    [[nodiscard]] uint32_t getId() const override { return id; }



private:
    //We have to store openGL texture data here bc openGL likes fucking with me
    void *rawData = nullptr;

    uint32_t id;
    uint32_t height;
    uint32_t width;

    //openGL stuff
    GLuint glId;
    GLenum dataFormat;
    GLenum internalFormat;




};


#endif //OPENGL_2D_TEXTURE_HPP
