//
// Created by Corbin Estes on 1/14/20.
//

#include "Input.cpp"

#include "KeyInput.hpp"
namespace InputSpace::Key {
    template <typename R, typename P>
    KeyInput<R, P>::KeyInput(int key, int modifiers, bool hold, bool toggle, R (*func)(std::vector<P>)) {
        trigger.key = key;
        trigger.modifiers = modifiers;
        repeatOnHold = hold;
        toggle_action = toggle;
        inputType = InputType::keyIn;
        action = func;
    }
    template <typename R, typename P>
    KeyInput<R, P>::KeyInput(int key, int modifiers, R (*func)(std::vector<P>), bool hold) {
        trigger.key = key;
        trigger.modifiers = modifiers;
        repeatOnHold = hold;
        toggle_action = false;
        inputType = InputType::keyIn;
        action = func;
    }
    template <typename R, typename P>
    KeyInput<R, P>::KeyInput(int key, int modifiers, bool toggle, R (*func)(std::vector<P>)) {
        trigger.key = key;
        trigger.modifiers = modifiers;
        repeatOnHold = false;
        toggle_action = toggle;
        inputType = InputType::keyIn;
        action = func;
    }
    template <typename R, typename P>
    KeyInput<R, P>::KeyInput(int key, int modifiers, R (*func)(std::vector<P>)) {
        trigger.key = key;
        trigger.modifiers = modifiers;
        repeatOnHold = false;
        toggle_action = false;
        inputType = InputType::keyIn;
        action = func;
    }
}
