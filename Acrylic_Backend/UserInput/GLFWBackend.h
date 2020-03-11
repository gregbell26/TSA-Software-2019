//
// Created by Corbin Estes on 3/11/20.
//

#ifndef ACRYLIC2D_GLFWBACKEND_H
#define ACRYLIC2D_GLFWBACKEND_H

#include "WindowBackend.hpp"



class GLFWBackend: public WindowBackend {
    enum class keys {};
    enum class mods {
        Shift = GLFW_MOD_SHIFT,
        Control = GLFW_MOD_CONTROL,
        Alt = GLFW_MOD_ALT,
        Super = GLFW_MOD_SUPER,
        CapLock = GLFW_MOD_CAPS_LOCK,
        NumLock = GLFW_MOD_NUM_LOCK,
    };
public:
    KeyMod onKeyPress() override;
    A2D_coordPair onMouseMove() override;
    MouseButtons onMouseButton() override;
    KeyCode convertKeyToA2DCode(int, int, KeyMod) override;


};


#endif //ACRYLIC2D_GLFWBACKEND_H
