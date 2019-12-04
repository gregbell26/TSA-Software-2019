//
// Created by coolh on 11/6/2019.
//

#include "acrylic_bitmap.h"

//---------------------------PIXEL-CONSTRUCTORS-----------------------------------
ImageLoaders::Bitmaps::Image::Pixel::Pixel()
{
    red = 0x00;
    green = 0x00;
    blue = 0x00;
    alpha = 0xFF;
}

ImageLoaders::Bitmaps::Image::Pixel::Pixel(char r, char g, char b, char a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}



//---------------------------IMAGE_CONSTRUCTORS-----------------------------------------
ImageLoaders::Bitmaps::Image::Image(const std::string& FileName) {
    std::ifstream is(FileName, std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
//                int length = is.tellg();
        length = is.tellg();
        is.seekg(0, is.beg);

        char *buffer = new char[length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(buffer, length);

        if (is) {
            std::cout << "all characters read successfully.";
        } else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();

        int *bff2 = new int[length];

        for (int i = 0; i < length; i++) {
            unsigned char v = buffer[i];
            if (v == '\0') {
                bff2[i] = 0;
            } else {
                bff2[i] = (int) v;
            }
        }
        std::cout << "msg start \n";
        int offset = bff2[10];
        height = bff2[18];
        width = bff2[22];
        bytes = bff2[28] / 8;

        length = height * width * bytes;

        std::cout << "Offset = " << offset << " Hight = " << height << " Width = " << width << " \n";

        imageData = new unsigned char[length]();

        for (int i = offset; i < length; i++) {
            imageData[i - offset] = bff2[i];
        }
        std::cout << "\n end ";
        // ...buffer contains the entire file...

        delete[] bff2;
        delete[] buffer;
    }
}

void ImageLoaders::Bitmaps::Image::PrintInfo()
{
    std::cout << (
            "Height: " + std::to_string(height) + "\n" +
            "Width: " + std::to_string(width) + "\n" +
            "Length: " + std::to_string(length) + "\n" +
            "Bytes: " + std::to_string(bytes) + "\n"
    );
}

void ImageLoaders::Bitmaps::Image::Print()
{
    std::cout << "\n";
    for (int i = 0; i < length; i ++)
    {
        if ((i) % bytes == 0)
        {
            std::cout << "(";
        }
        std::cout << std::to_string(imageData[i]);

        if ((i) % bytes == bytes - 1)
        {
            std::cout << "), ";
        }
        else
        {
            std::cout << ", ";
        }
        if ((i) % (width * bytes) == (width * bytes) - 1)
        {
            std::cout << "\n";
        }
    }
}

void ImageLoaders::Bitmaps::Image::Write(const std::string &FileName)
{
    std::fstream fs(FileName, std::ios_base::out | std::ios_base::binary);

    int Offset = 138;

    std::cout << "Length:" << length << std::endl;
    std::cout << "Offset:" << Offset << std::endl;
    std::cout << "Total:" << length + Offset << std::endl;

    auto * Data = new unsigned char[length + Offset];

    for (int i = 0; i < Offset; i++)
    {
        Data[i] = bmpData[i];
    }
    for (int i = 0; i < length; i++)
    {
        Data[i + Offset] = imageData[i];
        std::cout << "Data[" << i << "] = " << (int)Data[i + Offset] << "\n";
    }

    Data[10] = (unsigned char)Offset;
    Data[18] = (unsigned char)height;
    Data[22] = (unsigned char)width;
    Data[28] = (unsigned char)(bytes * 8);

    fs.write((const char *)Data, length + Offset);

    fs.close();

    delete[] Data;

    std::cout << "The BMP has been written.\n";
}