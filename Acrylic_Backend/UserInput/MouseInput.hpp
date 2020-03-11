//
// Created by Corbin Estes on 3/7/20.
//

#ifndef ACRYLIC2D_MOUSEINPUT_HPP
#define ACRYLIC2D_MOUSEINPUT_HPP


#include "Keys.hpp"

template <typename T>
class Mouse {
    std::map<MouseButtons, std::function<T>> buttons;
    std::function<T(A2D_coordPair)> cursorFunction;
public:
    Mouse<T> ();
    explicit Mouse<T> (std::map<MouseButtons, std::function<T>>);

    void check(int);
    void addButtonBinding(MouseButtons, std::function<T>);

    T cursorMove(A2D_coordPair);
    void setCursorFunction(std::function<T(A2D_coordPair)>);
};

#endif //ACRYLIC2D_MOUSEINPUT_HPP
