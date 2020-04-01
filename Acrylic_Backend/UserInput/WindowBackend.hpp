//
// Created by Corbin Estes on 3/4/20.
//

#ifndef ACRYLIC2D_WINDOWBACKEND_H
#define ACRYLIC2D_WINDOWBACKEND_H

#include "Keys.hpp"
#include "KeyInput.hpp"
#include "MouseInput.hpp"


template <typename K, typename M, typename C>
class WindowBackend {
public:
    virtual void setOnKey(K) = 0;
    virtual void setOnMouseButton(M) = 0;
    virtual void setOnMouseMove(C) = 0;
    virtual void addToKeyMap(int, int, int, KeyTriple) = 0;
    virtual KeyTriple convertKeyToA2DCode(int, int, int) = 0;
};

#endif //ACRYLIC2D_WINDOWBACKEND_H
