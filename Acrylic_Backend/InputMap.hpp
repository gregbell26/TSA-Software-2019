//
// Created by Corbin Estes on 1/16/20.
//

#ifndef ACRYLIC2D_INPUTMAP_HPP
#define ACRYLIC2D_INPUTMAP_HPP

#include <iostream>
#include "Input.hpp"
#include "KeyInput.hpp"
#include "MouseInput.hpp"


namespace InputSpace{
    class InputMap {
        std::vector<Input> inputList;
    public:
        InputMap();
        explicit InputMap(std::vector<Input> *list);
        void addInput(Input newIn);
        void addInput(std::vector<Input> newIn);

        const std::vector<Input> &getInputList() const;
    };
}



#endif //ACRYLIC2D_INPUTMAP_HPP
