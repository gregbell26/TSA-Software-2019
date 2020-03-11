//
// Created by Corbin Estes on 3/4/20.
//

#ifndef ACRYLIC2D_WINDOWBACKEND_H
#define ACRYLIC2D_WINDOWBACKEND_H

#include "Keys.hpp"

class WindowBackend {
public:
    virtual KeyMod onKeyPress() = 0;
    virtual MouseButtons onMouseButton() = 0;
    virtual A2D_coordPair onMouseMove() = 0;
    virtual KeyCode convertKeyToA2DCode(int, int, KeyMod) = 0;
};

#endif //ACRYLIC2D_WINDOWBACKEND_H
