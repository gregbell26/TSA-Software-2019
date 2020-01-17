#ifndef PLEXI_TEXTURE_HPP
#define PLEXI_TEXTURE_HPP


namespace Plexi::Texture {


    uint32_t create2DTexture(TextureCreateInfo& createInfo, const Plexi::PLEXI_GFX_BACKENDS& backendToUse);

    uint32_t createFontFace(FT_Face fontFace, uint32_t charCount, const Plexi::PLEXI_GFX_BACKENDS& backendToUse);



}
#endif //PLEXI_TEXTURE_HPP
