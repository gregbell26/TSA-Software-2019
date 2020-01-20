//
// Created by Corbin Estes on 1/17/20.
//

#ifndef ACRYLIC2D_KEYINPUT_HPP
#define ACRYLIC2D_KEYINPUT_HPP

#include <GLFW/glfw3.h>
//#include "Input.hpp"
namespace Inputs::Key{
    GLFWwindow* getWindowRef(GLFWwindow*, int);

    template <class R>
    class KeyInput: public Input<R> {
    public:
        R (*action)(GLFWwindow*, int act);
        Trigger key = {};
        explicit KeyInput(std::vector<KeyInput<GLFWwindow *>> *);
        KeyInput(int key, std::vector<KeyInput<GLFWwindow *>> *);
        KeyInput(int key, int modifiers, std::vector<KeyInput<GLFWwindow *>> *);
        KeyInput(int key, R (*action)(GLFWwindow *, int), std::vector<KeyInput<R>> *);
        KeyInput(int key, int modifiers, R (*action)(GLFWwindow *, int), std::vector<KeyInput<R>> *);

        void setAction(R (*action)(GLFWwindow *, int));

//        std::function<R(GLFWwindow*, int)> getAction() const;

        InputType getType();
    };

}


#endif //ACRYLIC2D_KEYINPUT_HPP
