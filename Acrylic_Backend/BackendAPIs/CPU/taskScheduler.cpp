// Created by Gabriel Bergeson oct. 2019

#include "TaskScheduler.hpp"

//#include <pthread.h>

#include <map>
#include <string>
#include <vector>
//#include <vcruntime_typeinfo.h>
#include <thread>

// Gets the function pointer, elapse time and       start time if applicable
void TaskScheduler::addTask(int cycles, int start, void (*function)())
{
    // Initialize typeid non boolean values
//    const type_info;

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
    // Checking when a thread is finished
    int threadCount = 0;
    bool threadCheck = false;

    // Creat thread pool
    // std::thread threadPool[100];



    std::vector<std::thread> threadPool;

    for (int i = 0; i < 100; i++)
    {
        threadPool[i].join();
    }


    // Creates a task
    Task task;
    // Creat array for Tasks
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
                if (threadPool[threadCount-1].joinable())
                {
                    // Create a thread using member function
                    std::thread th(taskPool[taskNumber-1].function, *taskPool[taskNumber-1].function);//note: in instantiation of function template specialization 'std::__1::thread::thread<void *&, void>' requested here
                    threadPool.push_back(th);//note: in instantiation of member function 'std::__1::vector<std::__1::thread, std::__1::allocator<std::__1::thread> >::push_back' requested here

                    // Badness
                    /*std::thread transfer = taskPool[taskNumber-1].function;
                    transfer.detach() = ;
                    threadPool.push_back(taskPool[taskNumber-1].function);

                    std::thread threadPool[threadCount](taskPool[taskNumber-1].function);

                    threadPool[threadCount] = std::thread(taskPool[taskNumber-1].function);
*/
                    threadCheck = true;
                }
                else
                {
                    threadCount++;
                }

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
