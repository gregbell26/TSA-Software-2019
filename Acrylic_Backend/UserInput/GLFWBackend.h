//
// Created by Corbin Estes on 3/11/20.
//

#ifndef ACRYLIC2D_GLFWBACKEND_H
#define ACRYLIC2D_GLFWBACKEND_H

#include "WindowBackend.hpp"

class GLFWBackend: public WindowBackend<void (GLFWwindow*, int, int, int, int),
        void(GLFWwindow*, int, int, int), void(GLFWwindow*, double, double)> {
    std::map<KeyTriple, KeyTriple> modMap = {};
    static Keyboard<void (GLFWwindow*, int, int, int, int)> keyboard;
    static Mouse<void (GLFWwindow*, int, int, int), void(GLFWwindow*, double, double)> mouse;
public:
    void setOnKey(std::function<void (GLFWwindow*, int, int, int, int)>) override;
    void setOnMouseButton(std::function<void (GLFWwindow*, int, int, int)>) override;
    void setOnMouseMove(std::function<void (GLFWwindow*, double, double)>) override;
    void addToKeyMap(int, int, int, KeyTriple) override;
    static void keyFunc(GLFWwindow*, int, int, int, int);
    static void mouseButtonFunc(GLFWwindow*, int, int, int);
    static void mouseMoveFunc(GLFWwindow*, double, double);
    KeyTriple convertKeyToA2DCode(int, int, int) override;
    void init();
};


#endif //ACRYLIC2D_GLFWBACKEND_H
