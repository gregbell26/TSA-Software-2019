//
// Created by Corbin Estes on 3/5/20.
//
#include "KeyInput.hpp"

template <typename T>
std::map<KeyTriple, std::function<T>> keyList;

void help(){

}

template <typename T>
Keyboard<T>::Keyboard() {
    keyList<void()>.insert(std::pair<KeyTriple, std::function<void()>>(KeyTriple(A2D_h, A2D_MOD_NONE), help));
}
template <typename T>
Keyboard<T>::Keyboard(std::map<KeyTriple, std::function<T>> keyList){
    keys = keyList;
}

template <typename T>
void Keyboard<T>::check(KeyTriple key){
    keys.at(key);
}

template <typename T>
void Keyboard<T>::addKeyBinding(KeyTriple key, std::function<T> action){
    keys.insert(std::pair(key, action));
}

template <typename T>
void Keyboard<T>::removeKeyBinding(KeyTriple key) {
    keys.erase(key);
}

