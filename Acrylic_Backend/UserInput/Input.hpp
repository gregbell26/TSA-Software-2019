//
// Created by Corbin Estes on 1/17/20.
//

#ifndef ACRYLIC2D_INPUT_HPP
#define ACRYLIC2D_INPUT_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"

namespace Inputs{
    struct trigger {
        int key;
        int modifiers;
    }
namespace InputSpace {
    union Returns {
        char str[100]{};
        int integer;
        float decimal;
        double Double;
        char character;

        explicit Returns(int i);
        explicit Returns(double d);
        explicit Returns(bool b);
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
        trigger key = {};
        Input();
        Input(std::vector<Input<GLFWwindow *>> *, InputType type);
        Input(int key, std::vector<Input<GLFWwindow *>> *, InputType type);
        Input(int key, int modifiers, std::vector<Input<R>> *, InputType type);
        Input(int key, R (*action)(GLFWwindow *), std::vector<Input<R>> *, InputType type);
        Input(int key, int modifiers, R (*action)(GLFWwindow *), std::vector<Input<R>> *, InputType type);

        void setKey(const trigger &key);
        virtual void setAction(R (*action)(GLFWwindow *));

        const trigger &getKey() const;

        virtual std::function<R(GLFWwindow*)> getAction() const;

        virtual InputType getType();
        Input(int key, int modifiers, bool hold, bool toggle, Returns (*func)(GLFWwindow *));
        Input(int key, int modifiers, bool toggle, Returns (*func)(GLFWwindow *));
        Input(int key, int modifiers, Returns (*func)(GLFWwindow *));
    };
}


#endif //ACRYLIC2D_INPUT_HPP
