//
// Created by coolh on 11/6/2019.
//

#include "acrylic_bitmap.h"
namespace A2D::Filesystem::ImageLoaders::Bitmaps {
    const unsigned char bmpData[] = // All values are little-endian
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
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, // Unused R, G, B entries for color space
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
}

//---------------------------IMAGE_CONSTRUCTORS-----------------------------------------
A2D::Filesystem::ImageLoaders::Bitmaps::Image::Image(const std::string& FileName) {
    logInformation("Image Start Loading")
    std::ifstream is(FileName, std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
        //                int length = is.tellg();
        length = static_cast<int>(is.tellg());
        is.seekg(0, is.beg);

        char* buffer = new char[length];
        std::string m = "Reading " + length;//bc you can oly add strings once
        logInformation(m + " characters... ")
            // read data as a block:
            is.read(buffer, length);

        if (is) {
            logInformation("all characters read successfully.")
        }
        else
        {
            std::string m = "error: only " + is.gcount();//bc you can oly add strings once
            logError(m + " could be read")
        }
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
        logInformation("Extracting header information")
        int offset;
        try{
        offset = bff2[10];
        height = bff2[18] | (bff2[19] << 8) | (bff2[20] << 16) | (bff2[21] << 24);
        width = bff2[22] | (bff2[23] << 8) | (bff2[24] << 16) | (bff2[25] << 24);
        bytes = bff2[28] / 8;
        }
        catch (std::out_of_range){
            logError("File smaller then expected header length")
            return;
        }

        length = height * width * bytes;
        m = "";
        m = m + ("Offset = " + offset) + (" Height = " + height) + (" Width = " + width);
        logInformation(m)

        imageData = new unsigned char[length]();

        for (int i = offset; i < length; i++) {
            imageData[i - offset] = bff2[i];
        }
        // ...buffer contains the entire file...

        delete[] bff2;
        delete[] buffer;
        logInformation("Image Loaded");
    }
    else
    {
        std::string m = "";
        m = m + "File: "+FileName+" Not Found Loading default Image instead.";
        logWarning(m)
        logError("default image not implemented returnig null image instead.");
    }
}

void A2D::Filesystem::ImageLoaders::Bitmaps::Image::PrintInfo()
{
    std::cout << (
            "Height: " + std::to_string(height) + "\n" +
            "Width: " + std::to_string(width) + "\n" +
            "Length: " + std::to_string(length) + "\n" +
            "Bytes: " + std::to_string(bytes) + "\n"
    );
}

void A2D::Filesystem::ImageLoaders::Bitmaps::Image::Print()
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

void A2D::Filesystem::ImageLoaders::Bitmaps::Image::Write(const std::string &FileName)
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

