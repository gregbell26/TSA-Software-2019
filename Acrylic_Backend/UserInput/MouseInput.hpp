//
// Created by Corbin Estes on 1/14/20.
//

#ifndef ACRYLIC2D_MOUSEINPUT_HPP
#define ACRYLIC2D_MOUSEINPUT_HPP

namespace InputSpace::Mouse {
    template<typename R, typename P>
    class MouseButtonInput : public Input {
    public:
        MouseButtonInput(int key, bool hold, bool toggle, R (*func)(std::vector<P>));

        MouseButtonInput(int key, bool toggle, R (*func)(std::vector<P>));

        MouseButtonInput(int key, R (*func)(std::vector<P>), bool hold);

        MouseButtonInput(int key, R (*func)(std::vector<P>));
    };

    template<typename R, typename P>
    class CursorInput : public Input {
    public:
        bool mouseButtonHeld;

        explicit CursorInput(R (*func)(std::vector<P>));

        CursorInput(bool mouseButtonHeld, R (*func)(std::vector<P>));
    };
}

#endif //ACRYLIC2D_MOUSEINPUT_HPP
