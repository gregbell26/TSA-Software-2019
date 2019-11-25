// Created by Gabriel Bergeson oct. 2019

#include "TaskScheduler.hpp"

//#include <pthread.h>

#include <map>
#include <string>
#include <vector>
#include <vcruntime_typeinfo.h>
#include <thread>

// Gets the function pointer, elapse time and       start time if applicable
void TaskScheduler::addTask(int cycles, int start, void* function)
{
    // Initialize typeid non boolean values
    const type_info;

    // Checks for void function type
    if (typeid(function).name() == typeid(void).name())
    {
        Cycles = cycles;
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
    // Checking when a thread is finisheded
    int threadCount = 0;
    bool threadCheck = false;

    std::thread threadPool[100];
    Task task;
    std::vector<Task> taskPool;
    while (Run)
    {
        // Checks to ensure the function cycled
        // Makes and queues new function
        if (taskPool[taskNumber--].function != Function
        && taskPool[taskNumber--].cycles != Cycles
        && taskPool[taskNumber--].start != Start)
        {
            // Creates name of the task to put into a structure

            // Creates and defines the task
            task.function = Function;
            task.cycles = Cycles;
            task.start = Start;
            // Moves the task to the array
            taskPool.push_back(task);
            taskNumber++;

            while (!threadCheck)
            {
                /// Yes I commented this out cause it was breaking stuff
//                if (/*TODO: check to make sure the thread is done*/)
//                {
//                    threadPool[threadCount](taskPool[taskNumber-1].function);
//                    threadCheck = true;
//                }
//                else
//                {
//                    threadCount++;
//                }

                if (threadCount >= 99)
                {
                    threadCheck = true;
                }
            }
            threadCheck = false;
        }
    }
}
// Checks queue to see if there is space for any threads
int TaskScheduler::assesQueue(Task task)
{
    int number = 0;

    return taskNumber;
}
// Stops all threads
void TaskScheduler::terminateThread()
{
    Run = false;
}

Task::Task() {

}
