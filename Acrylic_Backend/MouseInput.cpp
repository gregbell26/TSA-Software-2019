//
// Created by Corbin Estes on 1/14/20.
//

#include "MouseInput.hpp"
namespace InputSpace::Mouse{
    template <typename R, typename P>
    MouseButtonInput<R, P>::MouseButtonInput(int key, bool hold, bool toggle, R (*func)(std::vector<P>)){
        trigger.key = key;
        repeatOnHold = hold;
        toggle_action = toggle;
        inputType = InputType::mouseButton;
        action = func;
    }
    template <typename R, typename P>
    MouseButtonInput<R, P>::MouseButtonInput(int key, R (*func)(std::vector<P>), bool hold){
        trigger.key = key;
        repeatOnHold = hold;
        toggle_action = false;
        inputType = InputType::mouseButton;
        action = func;
    }
    template <typename R, typename P>
    MouseButtonInput<R, P>::MouseButtonInput(int key, bool toggle, R (*func)(std::vector<P>)){
        trigger.key = key;
        repeatOnHold = false;
        toggle_action = toggle;
        inputType = InputType::mouseButton;
        action = func;
    }
    template <typename R, typename P>
    MouseButtonInput<R, P>::MouseButtonInput(int key, R (*func)(std::vector<P>)){
        trigger.key = key;
        repeatOnHold = false;
        toggle_action = false;
        inputType = InputType::mouseButton;
        action = func;
    }
    template <typename R, typename P>
    CursorInput<R, P>::CursorInput(R (*func)(std::vector<P>)){
        mouseButtonHeld = false;
        inputType = InputType::cursorMove;
        action = func;
    }
    template <typename R, typename P>
    CursorInput<R, P>::CursorInput(bool held, R (*func)(std::vector<P>)){
        mouseButtonHeld = held;
        inputType = InputType::cursorMove;
        action = func;
    }

}
