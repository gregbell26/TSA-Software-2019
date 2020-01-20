//
// Created by Corbin Estes on 1/17/20.
//

#ifndef ACRYLIC2D_MOUSEINPUT_HPP
#define ACRYLIC2D_MOUSEINPUT_HPP

#include "Input.hpp"
namespace Inputs::Mouse{
    GLFWwindow* getWindowRef(GLFWwindow*, int);
    template <class R>
    class MouseInput: public Input<R> { //Mouse button functions
    public:
        R (*action)(GLFWwindow*, int);
        Trigger key = {};
        explicit MouseInput(std::vector<MouseInput<GLFWwindow *>> *list);
        MouseInput(int key, std::vector<MouseInput<GLFWwindow *>> *list);
        MouseInput(int key, int modifiers, std::vector<MouseInput<GLFWwindow *>> *list);
        MouseInput(int key, R (*action)(GLFWwindow *, int), std::vector<MouseInput<R>> *list);
        MouseInput(int key, int modifiers, R (*action)(GLFWwindow *, int), std::vector<MouseInput<R>> *list);

        void setAction(R (*action)(GLFWwindow *, int));

//        std::function<R(GLFWwindow*, int)> getAction() const;

        InputType getType();
    };

    void logPosition(GLFWwindow* window, double xOff, double yOff);
    template <class R>
    class CursorInput: public Input<R> { //Scroll and Cursor move functions
    public:
        R (*action)(GLFWwindow*, double xOff, double yOff);
        explicit CursorInput(std::vector<CursorInput<void>> *list);
        CursorInput(R (*action)(GLFWwindow *, double, double), std::vector<CursorInput<R>> *list);

        void setAction(R (*action)(GLFWwindow *, double, double));

//        std::function<R(GLFWwindow*, double, double)> getAction() const;

        InputType getType();
    };
}


#endif //ACRYLIC2D_MOUSEINPUT_HPP
