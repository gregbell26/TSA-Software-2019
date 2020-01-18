#ifndef ACRYLIC_BITMAP_H
#define ACRYLIC_BITMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <ths/log.hpp>

namespace A2D::Filesystem::ImageLoaders::Bitmaps {

    struct Image
    {
        int height;
        int width;
        int length;
        int bytes;

        unsigned char * imageData;//Sorry, I renamed this so that it would be more clear and not confused with the main struct

        explicit Image(const std::string& FileName);

        explicit Image(std::string DirectFile);

        uint32_t Convert();

        void Default();
        
        void PrintInfo();

        void Print();

        char GetPixelValue(int x,int y,int P) //P 0=red 1=green 2=blue 3=alpha
        {
            return imageData[(x + (y * width)) * bytes + P ];
        }

        void SetPixelValue(int x, int y, int P, char v) //P 0=red 1=green 2=blue 3=alpha
        {
            imageData[(x + (y * width)) * bytes + P] = v;
        }

        void Write(const std::string& FileName);

    };

}

#endif //ACRYLIC_BITMAP_H
