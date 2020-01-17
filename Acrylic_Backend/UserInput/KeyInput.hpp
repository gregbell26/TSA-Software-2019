//
// Created by Corbin Estes on 1/14/20.
//

#ifndef ACRYLIC2D_KEYINPUT_HPP
#define ACRYLIC2D_KEYINPUT_HPP
namespace InputSpace::Key{
    template <typename R, typename P>
    class KeyInput : public Input {
    public:
        KeyInput(int key, int modifiers, bool hold, bool toggle, R (*func)(std::vector<P>));
        KeyInput(int key, int modifiers, bool toggle, R (*func)(std::vector<P>));
        KeyInput(int key, int modifiers, R (*func)(std::vector<P>), bool hold);
        KeyInput(int key, int modifiers, R (*func)(std::vector<P>));
    };
}


#endif //ACRYLIC2D_KEYINPUT_HPP
