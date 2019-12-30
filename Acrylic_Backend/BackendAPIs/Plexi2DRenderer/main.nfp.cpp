#include "acrylic_plexiRenderer_core.hpp"

#include <GLFW/glfw3.h>

int main(){
    Plexi::initPlexi();
    Plexi::TextureCreateInfo textureCreateInfo = {};
    textureCreateInfo.height = 1;
    textureCreateInfo.width = 1;
    textureCreateInfo.channelCount = 4;
    textureCreateInfo.dataSize = sizeof(uint32_t);
    uint32_t data = 0xffffffff;
    textureCreateInfo.textureData = &data;

    uint32_t plainWhiteTexture = Plexi::Texture::create2DTexture(textureCreateInfo, Plexi::getActiveBackend());
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
    }


//    std::cin.get();
    Plexi::cleanupPlexi();



    return 0;
}