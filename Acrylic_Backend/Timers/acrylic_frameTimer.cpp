#include "acrylic_frameTimer.h"


void A2D::Timers::FrameTimer::startTimer(){
    start = std::chrono::system_clock::now();
}
double A2D::Timers::FrameTimer::getTime(){
    std::chrono::time_point<std::chrono::system_clock> end;
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();
}
double A2D::Timers::FrameTimer::getFPS(unsigned frames){

    std::chrono::time_point<std::chrono::system_clock> end;
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    return frames / elapsed_seconds.count();
}