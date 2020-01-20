#ifndef PLEXI_FRAMETIMER_H
#define PLEXI_FRAMETIMER_H

#include <chrono>

namespace A2D::Timers{
    class FrameTimer {
        public:
        std::chrono::time_point<std::chrono::system_clock> start;
        void startTimer();

        double getTime();

        double getFPS(unsigned frames);
    };
}

#endif //PLEXI_FRAMETIMER_H
