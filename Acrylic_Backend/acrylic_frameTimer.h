//
// Created by jimmy on 1/18/2020.
//

#ifndef ACRYLIC2D_PLEXIFRAMETIMER_H
#define ACRYLIC2D_PLEXIFRAMETIMER_H

#include <chrono>

namespace Timer{
    class frameTimer {
        public:
        std::chrono::time_point<std::chrono::system_clock> start;
        void startTimer(){
            start = std::chrono::system_clock::now();
        }
        double getTime(){
            std::chrono::time_point<std::chrono::system_clock> end;
            end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;
            return elapsed_seconds.count();
        }
        double getFPS(unsigned frames){

            std::chrono::time_point<std::chrono::system_clock> end;
            end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;

            return frames / elapsed_seconds.count();
        }
    };
}

#endif //ACRYLIC2D_PLEXIFRAMETIMER_H
