#ifndef ACRYLIC2D_INPUTS_HPP
#define ACRYLIC2D_INPUTS_HPP

//#include "Input.hpp"
//#include "KeyInput.hpp"
//#include "MouseInput.hpp"

namespace Inputs {
    template <typename T>
    std::vector<Input<T>> inputList;
    template <typename T>
    std::vector<Key::KeyInput<T>> keyInputList;
    template <typename T>
    std::vector<Mouse::MouseInput<T>> mouseInputList;
    template <typename T>
    std::vector<Mouse::CursorInput<T>> cursorInputList;

    //Key Callback
    //Runs through all key activated inputs and runs them if they match the pressed key
    template <typename T>
    T runKey(GLFWwindow* window, int key, int scancode, int action, int mods);

    //Mouse Button Callback
    //Runs through all mouse activated inputs and runs them if they match the pressed button
    template <typename T>
    T runMouseButton(GLFWwindow* window, int button, int action, int mods);

    //Cursor Move
    //Runs all cursor and scroll activated functions
    template <typename T>
    T runCursorMove(GLFWwindow* window, double xPos, double yPos);

    //Sets callbacks
    void init();

    //Input constructors
    Input<GLFWwindow *> newInput(InputType type);
    Input<GLFWwindow *> newInput(int key, InputType type);
    Input<GLFWwindow*> newInput(int key, int modifiers, InputType type);
    template <typename R>
    Input<R> newInput(int key, R (*action)(GLFWwindow *), InputType type);
    template <class R>
    Input<R> newInput(int key, int modifiers, R (*action)(GLFWwindow *), InputType type);

    //KeyInput constructors
    Key::KeyInput<GLFWwindow*> newKeyInput();
    Key::KeyInput<GLFWwindow*> newKeyInput(int key);
    Key::KeyInput<GLFWwindow*> newKeyInput(int key, int modifiers);
    template <class R>
    Key::KeyInput<R> newKeyInput(int key, R (*action)(GLFWwindow *, int));
    template <class R>
    Key::KeyInput<R> newKeyInput(int key, int modifiers, R (*action)(GLFWwindow *, int));

    //MouseButtonInput constructors
    Mouse::MouseInput<GLFWwindow *> newMouseInput();
    Mouse::MouseInput<GLFWwindow*> newMouseInput(int key);
    Mouse::MouseInput<GLFWwindow*> newMouseInput(int key, int modifiers);
    template <class R>
    Mouse::MouseInput<R> newMouseInput(int key, R (*action)(GLFWwindow *, int));
    template <class R>
    Mouse::MouseInput<R> newMouseInput(int key, int modifiers, R (*action)(GLFWwindow *, int));

    //CursorMoveInput constructors
    Mouse::CursorInput<void> newCursorInput();
    template <class R>
    Mouse::CursorInput<R> newCursorInput(R (*action)(GLFWwindow *, double, double));
}


#endif //ACRYLIC2D_INPUTS_HPP
