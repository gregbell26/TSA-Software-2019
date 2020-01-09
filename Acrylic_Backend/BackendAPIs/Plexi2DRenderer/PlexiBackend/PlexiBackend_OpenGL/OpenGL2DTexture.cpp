#define PLEXI_LIBRARY_ACTIVE

#include  "../plexiShaders.hpp"
#include "./../plexiBuffer.hpp"
#include "./../plexiHelper.hpp"

#include "OpenGL2DTexture.hpp"

void OpenGL2DTexture::createTexture(const PlexiTextureData& data, uint32_t size, uint32_t in_height, uint32_t in_width, uint32_t channelCount) {
    this->height = in_height;
    this->width = in_width;

    internalFormat = (channelCount == 4) ? GL_RGBA8 : GL_RGB8;
    dataFormat = (channelCount == 4) ? GL_BGRA : GL_BGR;


    if(data.usingGenericType) {
        rawData.generic = (void*)malloc(size);
        memcpy(rawData.generic, data.dataType.generic, size);
    }
    else {
        rawData.image = (unsigned char*) malloc(size);
        memcpy(rawData.image, data.dataType.image, size);
    }
//    *rawData = *data;//Copy the pointer data //This will most likely segfault

    usingGenericType = data.usingGenericType;

    glGenTextures(1, &glId);//Gen an ID

}


void OpenGL2DTexture::bind(uint32_t textureSlot) {
    //todo add texture slotting
    glBindTexture(GL_TEXTURE_2D, glId);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->width, this->height,0, dataFormat, GL_UNSIGNED_BYTE, (usingGenericType ? rawData.generic : rawData.image));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void OpenGL2DTexture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGL2DTexture::~OpenGL2DTexture() {
    glDeleteTextures(1, &glId);//This is safe and if the texture doesn't corrospond to an existing texture then nothing will happen
//    delete rawData;
}
