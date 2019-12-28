#ifndef OPENGL_2D_TEXTURE_HPP
#define OPENGL_2D_TEXTURE_HPP

class OpenGL2DTexture: public Plexi2DTexture {
public:
    void createTexture(void* data, uint32_t size, uint32_t height, uint32_t width, uint32_t channelCount) override;

    void bind(uint32_t textureSlot) override; // We can only have one texture slot in openGL 4.1 so we are ignoring this

    void unbind() override;

    uint32_t getId() override { return id; }

    ~OpenGL2DTexture() override;


private:
    //We have to store openGL texture data here bc openGL likes fucking with me
    void *rawData = nullptr; //if we have an image

    uint32_t id = 0;
    uint32_t height;
    uint32_t width;

    //openGL stuff
    GLuint glId;
    GLenum dataFormat;
    GLenum internalFormat;




};


#endif //OPENGL_2D_TEXTURE_HPP
