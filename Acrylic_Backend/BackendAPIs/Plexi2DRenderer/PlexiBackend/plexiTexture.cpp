#include "plexiShaders.hpp"
#include "plexiBuffer.hpp"
#include "plexiHelper.hpp"
#include "acrylic_plexiBackend.hpp"
#include "./../plexi_usrStructs.hpp"

#include "plexiTexture.hpp"


void Plexi::Texture::create2DTexture(Plexi::TextureCreateInfo &createInfo) {
    Plexi2DTexture* newTexture = GFXBackendMap[activeBackend]->getNewTexture();

    if(createInfo.fromImage){
        newTexture->createTextureFromImage();
    } else {
        newTexture->createTextureFromColor();
    }

    GFXBackendMap[activeBackend]->addTexture(newTexture);
}
