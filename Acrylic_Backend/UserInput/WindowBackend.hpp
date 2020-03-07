//
// Created by Corbin Estes on 3/4/20.
//

#ifndef ACRYLIC2D_WINDOWBACKEND_H
#define ACRYLIC2D_WINDOWBACKEND_H

#include "Keys.hpp"

template <typename T>
class WindowBackend {
public:
    virtual T getCursorPos() = 0;
    template <typename R>
    virtual R* getWindowPointer() = 0;
    virtual keys convert(int) = 0;
};

#endif //ACRYLIC2D_WINDOWBACKEND_H
