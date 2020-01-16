#include "acrylic_font.hpp"

namespace A2D::Filesystem::Loaders::Font {
    const std::filesystem::path DEFAULT_FONT_PATH = "./fonts/";
}

A2D::Filesystem::Loaders::Font::Font::Font() {
    if(FT_Init_FreeType(&ftLibrary) != FT_Err_Ok ){
        logError("Failed to initialize FreeType")
        init = false;
        return;
    }
    init = true;
}

std::filesystem::path A2D::Filesystem::Loaders::Font::Font::locateFont(const std::string &fontName) {
    std::filesystem::path pathToCheck = DEFAULT_FONT_PATH;
    pathToCheck += fontName;
    if(!std::filesystem::exists(pathToCheck)){
        logError("Failed to locate font \'" + fontName + "\'")
        return std::filesystem::path();
    }

    return pathToCheck;
}

void A2D::Filesystem::Loaders::Font::Font::createNewFont(const std::filesystem::path &fontPath, size_t fontSize) {
    createNewFont(fontPath, fontSize, 128); //By default load the first
}

void A2D::Filesystem::Loaders::Font::Font::createNewFont(const std::filesystem::path &fontPath, size_t fontSize,
                                                         uint32_t characterCount) {

    if(!init) {
        logError("Unable to load font; an initialization error occurred")
        return;
    }

    if(!std::filesystem::exists(fontPath)){
        logError("Font \'" + fontPath.filename().string() + "\' does not exist")
        return;
    }

    if(FT_New_Face(ftLibrary, fontPath.c_str(), 0, &ftFontFace) != FT_Err_Ok){
        logError("An error occurred while loading the font face \'" + fontPath.filename().string() + "\'")
        return;
    }

    //set font size in points - not pixels
    if(FT_Set_Char_Size(ftFontFace, 0, fontSize*64, 300, 300) != FT_Err_Ok){
        logError("An error occurred while setting the font size")
    }

}

A2D::Filesystem::Loaders::Font::Font::~Font() {
    FT_Done_Face(ftFontFace);
    FT_Done_FreeType(ftLibrary);
}
