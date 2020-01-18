//
// Created by Corbin Estes on 1/17/20.
//

#ifndef ACRYLIC2D_KEYINPUT_HPP
#define ACRYLIC2D_KEYINPUT_HPP

#include "Input.cpp"
namespace Inputs::Key{
    GLFWwindow* getWindowRef(GLFWwindow*, int);

    template <class R>
    class KeyInput: public Input<R> {
    public:
        R (*action)(GLFWwindow*, int act);
        trigger key = {};
        explicit KeyInput(std::vector<Input<GLFWwindow *>> *);
        KeyInput(int key, std::vector<Input<GLFWwindow *>> *);
        KeyInput(int key, int modifiers, std::vector<Input<GLFWwindow *>> *);
        KeyInput(int key, R (*action)(GLFWwindow *, int), std::vector<Input<R>> *);
        KeyInput(int key, int modifiers, R (*action)(GLFWwindow *, int), std::vector<Input<R>> *);

        void setAction(R (*action)(GLFWwindow *, int));

        std::function<R(GLFWwindow*, int)> getAction() const;

        InputType getType();
    };

}


#endif //ACRYLIC2D_KEYINPUT_HPP
