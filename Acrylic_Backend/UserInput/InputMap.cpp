//
// Created by Corbin Estes on 1/16/20.
//
#include "Input.hpp"
#include "KeyInput.hpp"
#include "MouseInput.hpp"

#include "InputMap.hpp"
namespace InputSpace{
    void init();
    Returns::Returns(int i) {}
    Returns::Returns(double d) {}
    Returns::Returns(bool b) {}
    Returns placeholder(std::vector<Returns> params){}
    template <typename R, typename P>
    Key::KeyInput<R, P> newKeyInput(int key, int modifiers, bool hold, bool toggle, R (*func)(std::vector<P>)){
        return Key::KeyInput(key, modifiers, hold, toggle, func);
    }
    template <typename R, typename P>
    Mouse::MouseButtonInput<R, P> newMouseButtonInput(int key, bool hold, bool toggle, R (*func)(std::vector<P>)){
        return Mouse::MouseButtonInput(key, hold, toggle, func);
    }
    template <typename R, typename P>
    Mouse::CursorInput<R, P> newCursorInput(bool mouseButtonHeld, R (*func)(std::vector<P>)){
        return Mouse::CursorInput(mouseButtonHeld, func);
    }
    void newInput(std::vector<InputMap *> map){
        InputType type = cursorMove; //User defined
        switch (type) {
            case mouseButton:
                map.at(0)->addInput(newMouseButtonInput(0, false, false, placeholder));
            case keyIn:
                map.at(0)->addInput(newKeyInput(0, 0, false, false, placeholder));
            case cursorMove:
                map.at(0)->addInput(newMouseButtonInput(0, false, false, placeholder));
        }
    }

    InputMap::InputMap(){
        std::vector<InputMap *> map;
        map.push_back(this);
        newKeyInput<void, std::vector<InputMap *>>(GLFW_KEY_N, 3, false, false, newInput(map));
        inputList.push_back(newKeyInput<>(GLFW_KEY_N, 3, false, false, newInput(map)))
    }
    InputMap::InputMap(std::vector<Input> *list){
        inputList = *list;
    }

    const std::vector<Input> &InputMap::getInputList() const {
        return inputList;
    }

    Returns run(std::map<std::string, Returns> parameters, InputType type, InputMap inputs) {
        for (int i = 0; i < inputs.getInputList().size(); i++){
            if (type == cursorMove) {
                if (glfwGetMouseButton(Plexi::getWindowRef(), 0) == GLFW_PRESS){
                    if (inputs.getInputList().at(i).inputType == cursorMove && inputs.getInputList().at(i).repeatOnHold){
                        return inputs.getInputList().at(i).action(Plexi::getWindowRef());
                    }
                } else {
                    if (inputs.getInputList().at(i).inputType){
                        return inputs.getInputList().at(i).action(Plexi::getWindowRef());
                    }
                }
            }
            if (type == keyIn) {
                if (parameters.at("key").integer == inputs.getInputList().at(i).trigger.key) {
                    if (parameters.at("modifiers").integer == inputs.getInputList().at(i).trigger.modifiers){
                        return inputs.getInputList().at(i).action(Plexi::getWindowRef());
                    }
                }
            }
            if (type == mouseButton){
                if (parameters.at("key").integer == inputs.getInputList().at(i).trigger.key){
                    return inputs.getInputList().at(i).action(Plexi::getWindowRef());
                }
            }
        }
    }

    static void buttonCallback(GLFWwindow* window, int key, int scanCode, int action){
        std::map<std::string, Returns> param;
        param.insert(std::pair<std::string, Returns>("key", key));
        param.insert(std::pair<std::string, Returns>("action", action));
        run(&param, mouseButton);
    }
    static void cursorCallback(GLFWwindow* window, double xPos, double yPos){
        Returns mouseLeft = false;
        Returns mouseRight = false;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            mouseLeft = true;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
            mouseRight = true;
        }
        std::map<std::string, Returns> param;
        param.insert(std::pair<std::string, Returns>("xPos", xPos));
        param.insert(std::pair<std::string, Returns>("yPos", yPos));
        param.insert(std::pair<std::string, Returns>("leftButton", mouseLeft));
        param.insert(std::pair<std::string, Returns>("rightButton", mouseRight));
        run(&param, cursorMove);
    }
    static void scrollCallback(GLFWwindow* window, double xOff, double yOff){
        std::map<std::string, Returns> param;
        param.insert(std::pair<std::string, Returns>("xOffset", xOff));
        param.insert(std::pair<std::string, Returns>("yOffset", yOff));
        run(&param, cursorMove);
    }
    static void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
        Returns k = key;
        Returns a = action;
        std::map<std::string, Returns> param;
        param.insert(std::pair<std::string, Returns>("key", key));
        param.insert(std::pair<std::string, Returns>("action", action));
        param.insert(std::pair<std::string, Returns>("modifiers", mods));
        run(&param, keyIn);
    }
    void init() {
        initLogger("userIn", log_severity_information, log_mode_all)
        glfwSetKeyCallback(Plexi::getWindowRef(), keyCallback);
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), buttonCallback);
        glfwSetCursorPosCallback(Plexi::getWindowRef(), cursorCallback);
        glfwSetScrollCallback(Plexi::getWindowRef(), scrollCallback);
        logInformation("Input initialized")
    }
}
