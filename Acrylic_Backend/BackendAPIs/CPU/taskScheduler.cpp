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
//    if (typeid(&function) == typeid(void));
//    {
//        // Creates name of the task to put into a structure
//        std::stringstream ss;
//        ss << 'task' << taskNumber;
//        std::string name=ss.str();
//
//        taskNumber++;
//
//        Task 'name';
//    }
}

// Makes a structure from the passed information
int TaskScheduler::createTask()
{
    return 0;
}
// Runs the threads with an infinite loop checking the queue and executing threads
void TaskScheduler::threadRun()
{
    Task tasks = {{}};
    while (Run)
    {

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

}
