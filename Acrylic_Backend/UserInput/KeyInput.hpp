//
// Created by Corbin Estes on 3/5/20.
//

#ifndef ACRYLIC2D_KEYINPUT_H
#define ACRYLIC2D_KEYINPUT_H

#include "Keys.hpp"

template <typename T>
class Keyboard {
    std::map<KeyMod, std::function<T>> keys;
public:

    Keyboard<T> ();
    explicit Keyboard<T> (std::map<KeyMod, std::function<T>>);

    void check(KeyMod key);
    void addKeyBinding(KeyMod, std::function<T>);
    void removeKeyBinding(KeyMod);
};

#endif //ACRYLIC2D_KEYINPUT_H
