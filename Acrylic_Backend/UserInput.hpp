//
// Created by Corbin Estes on 12/4/19.
//

#ifndef ACRYLIC2D_USERINPUT_HPP
#define ACRYLIC2D_USERINPUT_HPP
#include <iostream>
#include <GLFW/glfw3.h>
#include "BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
namespace UserInput {
    union Returns {
        char str[100];
        int integer;
        float decimal;
        double Double;
        char character;
    };

    struct keyInfo {
        int key;
        int action;

        Returns (*func)(int action);
    };

    std::vector<keyInfo> keys;

//left button = 0 and right button = 1
    Returns (*mouseButtonFunctions[8])(int action);

    Returns (*scrollFunc)(double xoffset, double yoffset);

    Returns (*enterWindowFunc)();

    Returns (*exitWindowFunc)();

    Returns (*cursorMoveFunc)(double xpos, double ypos);

    Returns (*cursorPressedMoveFunc)(double xpos, double ypos);
}
#endif //ACRYLIC2D_USERINPUT_HPP
