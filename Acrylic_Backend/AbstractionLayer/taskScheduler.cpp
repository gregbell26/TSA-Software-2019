// Created by Gabriel Bergeson oct. 2019

#include "taskScheduler.hpp"

#include <pthread.h>

#include <map>
#include <string>

struct Task{
    // Teh pointer to the function
    void *function;
    // Stores the cycles of the processor that the function will run for
    int cycles;
    // Optional, for set start times of the function
    int Start;
};
// Gets the function pointer, elapse time and       start time if applicable
void passTask(int cycles, int start, void *function)
{
    // Checks for void function type
    if (typeid(*function) == typeid(void()));
    {
        stringstream ss;
        ss << 'task' << someNumber;
        string name=ss.str();
    }
}

// Makes a structure from the passed information
int creatTask()
{

}
// Runs the threads with an infinite loop checking the queue and executing threads
void threadRun()
{

}
// Checks queue to see if there is space for any threads
int assesQueue()
{

}
// Stops a thread
void terminateThread()
{

}
