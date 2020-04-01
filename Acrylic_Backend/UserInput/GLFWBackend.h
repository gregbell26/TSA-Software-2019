//
// Created by Corbin Estes on 3/11/20.
//

#ifndef ACRYLIC2D_GLFWBACKEND_H
#define ACRYLIC2D_GLFWBACKEND_H

#include "WindowBackend.hpp"

struct KeyTriple {
    int key;
    int mod;
    int action;

    KeyTriple(int _key, int _mod, int _action){
        key = _key;
        mod = _mod;
        action = _action;
    }
};

class GLFWBackend: public WindowBackend<void (GLFWwindow*, int, int, int, int),
        void(GLFWwindow*, int, int, int), void(GLFWwindow*, double, double)> {
    std::map<KeyTriple, KeyMod> modMap = {};
public:
    void setOnKey(std::function<void (GLFWwindow*, int, int, int, int)>) override;
    void setOnMouseButton(std::function<void (GLFWwindow*, int, int, int)>) override;
    void setOnMouseMove(std::function<void (GLFWwindow*, double, double)>) override;
    void addToKeyMap(int, int, int, KeyMod) override;
    KeyMod convertKeyToA2DCode(int, int, int) override;
};


#endif //ACRYLIC2D_GLFWBACKEND_H
