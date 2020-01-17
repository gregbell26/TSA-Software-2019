//
// Created by Corbin Estes on 12/11/19.
//

#include "Input.hpp"
#include "InputMap.hpp"

namespace InputSpace {

    Input::Input() {
        trigger.key = 0;
        trigger.modifiers = 0;
        repeatOnHold = false;
        toggle_action = false;
    }
    Input::Input(int key, int modifiers, bool hold, bool toggle, Returns (*func)(GLFWwindow *)){
        trigger.key = key;
        for (int i = 0; i < 3; ++i) {
            trigger.modifiers = modifiers;
        }
        repeatOnHold = hold;
        toggle_action = toggle;
        action = func;
    }


    Input::Input(int key, int modifiers, Returns (*func)(GLFWwindow *), bool hold){
        trigger.key = key;
        for (int i = 0; i < 3; ++i) {
            trigger.modifiers = modifiers;
        }
        repeatOnHold = hold;
        toggle_action = false;
        action = func;
    }
    Input::Input(int key, int modifiers, bool toggle, Returns (*func)(GLFWwindow *)){
        trigger.key = key;
        for (int i = 0; i < 3; ++i) {
            trigger.modifiers = modifiers;
        }
        repeatOnHold = false;
        toggle_action = toggle;
        action = func;
    }


    Input::Input(int key, int modifiers, Returns (*func)(GLFWwindow *)){
        trigger.key = key;
        for (int i = 0; i < 3; ++i) {
            trigger.modifiers = modifiers;
        }
        repeatOnHold = false;
        toggle_action = false;
        action = func;
    }


}
