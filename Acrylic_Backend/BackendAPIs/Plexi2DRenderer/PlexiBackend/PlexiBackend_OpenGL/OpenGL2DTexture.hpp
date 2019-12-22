#ifndef OPENGL_2D_TEXTURE_HPP
#define OPENGL_2D_TEXTURE_HPP

class OpenGL2DTexture: public Plexi2DTexture {
public:
    void createTextureFromImage() override;

    void createTextureFromColor() override;

    void bind(uint32_t textureSlot) override;

    uint32_t getId() override { return id; }

private:
    uint32_t id = 0;

};


#endif //OPENGL_2D_TEXTURE_HPP
