#ifndef ACRYLIC_FONT_HPP
#define ACRYLIC_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
//#include FT_OUTLINE_H

namespace A2D::Filesystem::Loaders::Font {

    class Font {
        FT_Library getFreeTypeLib() { return freeTypeLib; }


    private:
        FT_Library freeTypeLib;
    };


}

#endif //ACRYLIC_FONT_HPP