//
// Created by coolh on 11/6/2019.
//

#include "acrylic_bitmap.h"
#include <iostream>
#include <fstream>
#include <string>

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
        Pixel()
        {
            red = 0x00;
            green = 0x00;
            blue = 0x00;
            alpha = 0xFF;
        }

        Pixel(char r,char g,char b,char a)
        {
            red = r;
            green = g;
            blue = b;
            alpha = a;
        }
    };
    int Hight, Width,Length,Bytes;
    unsigned char * image;

    Image(std::string FileName)
    {
        std::ifstream is(FileName, std::ifstream::binary);
        if (is) {
            // get length of file:
            is.seekg(0, is.end);
            int length = is.tellg();
            is.seekg(0, is.beg);

            char * buffer = new char[length];

            std::cout << "Reading " << length << " characters... ";
            // read data as a block:
            is.read(buffer, length);

            if (is) {
                std::cout << "all characters read successfully.";
            }
            else
                std::cout << "error: only " << is.gcount() << " could be read";
            is.close();

            int * bff2 = new int[length];

            for (int i = 0; i < length; i++)
            {
                unsigned char v = buffer[i];
                if (v == '\0')
                {
                    bff2[i] = 0;
                }
                else
                {
                    bff2[i] = (int)v;
                }
            }
            std::cout << "msg start \n";
            int offset = bff2[10];
            Hight = bff2[18];
            Width = bff2[22];
            Bytes = bff2[28] / 8;

            Length = Hight * Width * Bytes;

            std::cout << "Offset = " << offset << " Hight = " << Hight << " Width = " << Width << " \n";

            image = new unsigned char[Length]();

            for (int i = offset; i < length; i++)
            {
                image[i - offset] = bff2[i];
            }
            std::cout << "\n end ";
            // ...buffer contains the entire file...

            delete[] bff2;
            delete[] buffer;
        }
    }
public :
    void PrintInfo()
    {
        std::cout << (
                "Hight: " + std::to_string(Hight) + "\n" +
                "Width: " + std::to_string(Width) + "\n" +
                "Length: " + std::to_string(Length) + "\n" +
                "Bytes: " + std::to_string(Bytes) + "\n"
        );
    }

    void Print()
    {
        std::cout << "\n";
        for (int i = 0; i < Length; i ++)
        {
            if ((i) % Bytes == 0)
            {
                std::cout << "(";
            }
            std::cout << std::to_string(image[i]);

            if ((i) % Bytes == Bytes - 1)
            {
                std::cout << "), ";
            }
            else
            {
                std::cout << ", ";
            }
            if ((i) % (Width*Bytes) == (Width*Bytes) - 1)
            {
                std::cout << "\n";
            }
        }
    }

    char GetPixelValue(int x,int y,int P) //P 0=red 1=green 2=blue 3=alpha
    {
        return image[(x+(y*Width))*Bytes +P];
    }

    void SetPixelValue(int x, int y, int P, char v) //P 0=red 1=green 2=blue 3=alpha
    {
        image[(x + (y*Width))*Bytes + P] = v;
    }

    void Write(std::string FileName)
    {
        std::fstream fs(FileName, std::ios_base::out | std::ios_base::binary);

        int Offset = 138;

        std::cout << "Length:" << Length << std::endl;
        std::cout << "Offset:" << Offset << std::endl;
        std::cout << "Total:" << Length + Offset << std::endl;

        unsigned char * Data = new unsigned char[Length + Offset];

        for (int i = 0; i < Offset; i++)
        {
            Data[i] = bmpData[i];
        }
        for (int i = 0; i < Length; i++)
        {
            Data[i + Offset] = image[i];
            std::cout << "Data[" << i << "] = " << (int)Data[i + Offset] << "\n";
        }

        Data[10] = (unsigned char)Offset;
        Data[18] = (unsigned char)Hight;
        Data[22] = (unsigned char)Width;
        Data[28] = (unsigned char)(Bytes * 8);

        fs.write((const char *)Data, Length + Offset);

        fs.close();

        delete[] Data;

        std::cout << "The BMP has been written.\n";
    }
};

