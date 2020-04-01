//
// Created by Corbin Estes on 3/7/20.
//

#ifndef ACRYLIC2D_MOUSEINPUT_HPP
#define ACRYLIC2D_MOUSEINPUT_HPP


#include "Keys.hpp"

//B refers to signature of the mouse button functions
//C refers to the return type of the cursor move functions (A2D_coordPair is always the parameter)
template <typename B, typename C>
class Mouse {
    std::map<MouseButtons, std::function<B>> buttons;
    std::function<C> cursorFunction;
public:
    Mouse<B, C> ();
    explicit Mouse<B, C> (std::map<MouseButtons, std::function<B>>);

    void check(int);
    void addButtonBinding(MouseButtons, std::function<B>);

    void removeButtonBinding(MouseButtons);

    void cursorMove(A2D_coordPair);
    void setCursorFunction(std::function<C>);
};

#endif //ACRYLIC2D_MOUSEINPUT_HPP
