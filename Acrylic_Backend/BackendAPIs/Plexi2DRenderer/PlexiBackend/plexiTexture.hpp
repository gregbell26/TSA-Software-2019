#ifndef PLEXI_TEXTURE_HPP
#define PLEXI_TEXTURE_HPP


namespace Plexi::Texture {
#ifndef PLEXI_LIBRARY_ACTIVE
    PLEXI_GFX_BACKENDS activeBackend;

    void setActiveBackend(PLEXI_GFX_BACKENDS& backend) { activeBackend = backend; }

#endif //PLEXI_LIBRARY_ACTIVE


    void create2DTexture(TextureCreateInfo& createInfo);



}
#endif //PLEXI_TEXTURE_HPP
