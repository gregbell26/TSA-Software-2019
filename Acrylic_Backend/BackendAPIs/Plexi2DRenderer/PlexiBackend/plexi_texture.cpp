#include "plexi_shaders.hpp"
#include "plexi_buffer.hpp"
#include "plexi_helper.hpp"
#include "plexi_backend.hpp"
#include "./../plexi_usrStructs.hpp"

#include "plexi_texture.hpp"


uint32_t Plexi::Texture::create2DTexture(Plexi::TextureCreateInfo &createInfo, const Plexi::PLEXI_GFX_BACKENDS &backendToUse) {
    if(!GFXBackendMap[backendToUse]) {
        logError("Texture Creation Failed: Invalid Backend")
        return 0;
    }
    if(!createInfo.textureData.dataType.generic && !createInfo.textureData.dataType.image){
        logError("Texture Creation Failed: Invalid Data")
         return 0;
    }

    Plexi2DTexture* newTexture = GFXBackendMap[backendToUse]->getNewTexture();

    newTexture->createTexture(createInfo.textureData, createInfo.dataSize, createInfo.height, createInfo.width, createInfo.channelCount);

    GFXBackendMap[backendToUse]->addTexture(newTexture);

    return newTexture->getId();
}

uint32_t Plexi::Texture::createFontFace(FT_Face fontFace, uint32_t charCount, const Plexi::PLEXI_GFX_BACKENDS& backendToUse) {
    return GFXBackendMap[backendToUse]->addFontFace(fontFace, charCount);
}
