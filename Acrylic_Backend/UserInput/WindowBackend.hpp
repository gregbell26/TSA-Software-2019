//
// Created by Corbin Estes on 3/4/20.
//

#ifndef ACRYLIC2D_WINDOWBACKEND_H
#define ACRYLIC2D_WINDOWBACKEND_H

#include "Keys.hpp"


template <typename K, typename M, typename C>
class WindowBackend {
public:
    virtual void setOnKey(std::function<K>) = 0;
    virtual void setOnMouseButton(std::function<M>) = 0;
    virtual void setOnMouseMove(std::function<C>) = 0;
    virtual void addToKeyMap(int, int, int, KeyMod) = 0;
    virtual KeyMod convertKeyToA2DCode(int, int, int) = 0;
};

#endif //ACRYLIC2D_WINDOWBACKEND_H
