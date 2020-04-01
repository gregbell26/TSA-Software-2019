//
// Created by Corbin Estes on 3/5/20.
//

#ifndef ACRYLIC2D_KEYINPUT_H
#define ACRYLIC2D_KEYINPUT_H

#include "Keys.hpp"

template <typename T>
class Keyboard {
    std::map<KeyTriple, std::function<T>> keys;
public:

    Keyboard<T> ();
    explicit Keyboard<T> (std::map<KeyTriple, std::function<T>>);

    void check(KeyTriple key);
    void addKeyBinding(KeyTriple, std::function<T>);
    void removeKeyBinding(KeyTriple);
};

#endif //ACRYLIC2D_KEYINPUT_H
