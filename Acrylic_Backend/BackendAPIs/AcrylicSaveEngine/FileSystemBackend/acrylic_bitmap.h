#ifndef ACRYLIC_BITMAP_H
#define ACRYLIC_BITMAP_H

#include <iostream>
#include <fstream>
#include <string>

namespace ImageLoaders::Bitmaps {

    unsigned char bmpData[] = // All values are little-endian
            {
                    0x42, 0x4D,             // Signature 'BM'
                    0xaa, 0x00, 0x00, 0x00, // Size: 170 bytes
                    0x00, 0x00,             // Unused
                    0x00, 0x00,             // Unused
                    0x8a, 0x00, 0x00, 0x00, // Offset to image data

                    0x7c, 0x00, 0x00, 0x00, // DIB header size (124 bytes)
                    0x04, 0x00, 0x00, 0x00, // Width (4px)
                    0x02, 0x00, 0x00, 0x00, // Height (2px)
                    0x01, 0x00,             // Planes (1)
                    0x20, 0x00,             // Bits per pixel (32)
                    0x03, 0x00, 0x00, 0x00, // Format (bitfield = use bitfields | no compression)
                    0x20, 0x00, 0x00, 0x00, // Image raw size (32 bytes)
                    0x13, 0x0B, 0x00, 0x00, // Horizontal print resolution (2835 = 72dpi * 39.3701)
                    0x13, 0x0B, 0x00, 0x00, // Vertical print resolution (2835 = 72dpi * 39.3701)
                    0x00, 0x00, 0x00, 0x00, // Colors in palette (none)
                    0x00, 0x00, 0x00, 0x00, // Important colors (0 = all)
                    0x00, 0x00, 0xFF, 0x00, // R bitmask (00FF0000)
                    0x00, 0xFF, 0x00, 0x00, // G bitmask (0000FF00)
                    0xFF, 0x00, 0x00, 0x00, // B bitmask (000000FF)
                    0x00, 0x00, 0x00, 0xFF, // A bitmask (FF000000)
                    0x42, 0x47, 0x52, 0x73, // sRGB color space
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Unused R, G, B entries for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma X entry for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma Y entry for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma Z entry for color space

                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown

                    // Image data:
                    //0xFF, 0x00, 0x00, 0x7F, // Bottom left pixel
                    //0x00, 0xFF, 0x00, 0x7F,
                    //0x00, 0x00, 0xFF, 0x7F,
                    //0xFF, 0xFF, 0xFF, 0x7F, // Bottom right pixel
                    //0xFF, 0x00, 0x00, 0xFF, // Top left pixel
                    //0x00, 0xFF, 0x00, 0xFF,
                    //0x00, 0x00, 0xFF, 0xFF,
                    //0xFF, 0xFF, 0xFF, 0xFF  // Top right pixel
            };

    struct Image
    {

        struct Pixel
        {
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            unsigned char alpha;

            Pixel();

            Pixel(char r,char g,char b,char a);
        };

        int height;
        int width;
        int length;
        int bytes;

        unsigned char * imageData;//Sorry, I renamed this so that it would be more clear and not confused with the main struct


        explicit Image(const std::string& FileName);



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
