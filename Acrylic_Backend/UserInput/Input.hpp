//
// Created by Corbin Estes on 1/17/20.
//

#ifndef ACRYLIC2D_INPUT_HPP
#define ACRYLIC2D_INPUT_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include <functional>
#include "../BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"

namespace Inputs{
    struct Trigger {
        int key;
        int modifiers;
    };
    enum InputType {
        none,
        cursorMove,
        keyPress,
        mouseButton,
    };

    GLFWwindow* getWindowRef(GLFWwindow* window);
    template <class R>
    class Input {
        InputType type;
    public:
        R (*action)(GLFWwindow*);
        Trigger key = {};
        Input();
        Input(std::vector<Input<GLFWwindow *>> *, InputType type);
        Input(int key, std::vector<Input<GLFWwindow *>> *, InputType type);
        Input(int key, int modifiers, std::vector<Input<GLFWwindow*>> *, InputType type);
        Input(int key, std::function<R(GLFWwindow *)> action, std::vector<Input<R>> *, InputType type);
        Input(int key, int modifiers,std::function<R(GLFWwindow *)> action, std::vector<Input<R>> *, InputType type);

        void setKey(const Trigger &key);
        virtual void setAction(R (*action)(GLFWwindow *));

        const Trigger &getKey() const;

        virtual std::function<R(GLFWwindow*)> getAction() const;

        virtual InputType getType();
    };
}


#endif //ACRYLIC2D_INPUT_HPP
