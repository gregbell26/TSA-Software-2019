//
// Created by Corbin Estes on 12/11/19.
//

#ifndef ACRYLIC2D_INPUT_HPP
#define ACRYLIC2D_INPUT_HPP
#include <iostream>
#include <GLFW/glfw3.h>
#include "BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"

namespace InputSpace {
    union Returns {
        char str[100]{};
        int integer;
        float decimal;
        double Double;
        char character;

        Returns(int i);
        Returns(double d);
        Returns(bool b);
    };

    enum InputType {
        mouseButton,
        cursorMove,
        keyIn
    };

    struct key {
        int key;
        int modifiers;
    };

    class Input {
    public:
        key trigger;
        InputType inputType;
        bool repeatOnHold;
        bool toggle_action;
        Returns (*action)(GLFWwindow *);
    public:
        Input();
        Input(int key, int modifiers, bool hold, bool toggle, Returns (*func)(GLFWwindow *));
        Input(int key, int modifiers, bool toggle, Returns (*func)(GLFWwindow *));
        Input(int key, int modifiers, Returns (*func)(GLFWwindow *), bool hold);
        Input(int key, int modifiers, Returns (*func)(GLFWwindow *));
    };
}


#endif //ACRYLIC2D_INPUT_HPP
