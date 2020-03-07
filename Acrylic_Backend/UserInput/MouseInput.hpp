//
// Created by Corbin Estes on 3/7/20.
//

#ifndef ACRYLIC2D_MOUSEINPUT_HPP
#define ACRYLIC2D_MOUSEINPUT_HPP

#include <functional>
#include <map>
#include "../BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "Keys.hpp"

template <typename T>
class Mouse {
    std::map<int, std::function<T>> buttons;
public:

    Mouse<T> ();
    explicit Mouse<T> (std::map<int, std::function<T>>);

    void check();
    void addButtonBinding(int, std::function<T>);
};



#endif //ACRYLIC2D_MOUSEINPUT_HPP
