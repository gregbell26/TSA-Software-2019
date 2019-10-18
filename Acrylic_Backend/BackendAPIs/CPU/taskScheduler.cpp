// Created by Gabriel Bergeson oct. 2019

#include "TaskScheduler.hpp"

//#include <pthread.h>

#include <map>
#include <string>
#include <vector>

// Gets the function pointer, elapse time and       start time if applicable
void TaskScheduler::addTask(int cycles, int start, void *function)
{
    // Checks for void function type
    if (typeid(function) == typeid(void));
    {
        Cycle = cycle;
        Start = start;
        Function = function;
    }
}

// Makes a structure from the passed information
int TaskScheduler::createTask()
{
    return 0;
}
// Runs the threads with an infinite loop checking the queue and executing threads
void TaskScheduler::threadRun()
{
    vector<Task> tasks;
    while (Run)
    {
        // Checks to ensure the function cycled
        if (tasks[taskNumber--].function == Function
        && tasks[taskNumber--].cycle == Cycles
        && tasks[taskNumber--].start == Start)
        {

        }
        // Makes and queues new function
        else {
            // Creates name of the task to put into a structure
            std::stringstream ss;
            ss << 'task' << taskNumber;
            std::string name = ss.str();

            // Creates and defines the task
            Task
            'name';
            'name'.function = Function;
            'name'.cycle = Cycles;
            'name'.start = Start;
            // Moves the task to the array
            tasks.push_back('name');
            taskNumber++;
        }
    }
}
// Checks queue to see if there is space for any threads
int TaskScheduler::assesQueue(Task task)
{
    return 0;
}
// Stops a thread
void TaskScheduler::terminateThread()
{
    Run = false;
}
