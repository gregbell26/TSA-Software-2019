#ifndef ACRYLIC_FONT_HPP
#define ACRYLIC_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <ths/log.hpp>
#include <filesystem>
#include <string>
//#include FT_OUTLINE_H

namespace A2D::Filesystem::Loaders::Font {
    class Font {
    public:
        Font();
        std::filesystem::path locateFont(const std::string& fontName);

        void createNewFont(const std::filesystem::path& fontPath, size_t fontSize);
        
        void createNewFont(const std::filesystem::path& fontPath, size_t fontSize, uint32_t characterCount);

        FT_Library getFreeTypeLib() { return ftLibrary; }
        FT_Face getLoadedFontFace() { return ftFontFace; }

        ~Font();


    private:
        FT_Library ftLibrary;
        FT_Face ftFontFace;
        bool init = false;
    };


}

#endif //ACRYLIC_FONT_HPP