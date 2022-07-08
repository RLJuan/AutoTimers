/**
 * @file TimerTask.h
 * @author Juan R. López (sfcduino@gmail.com)
 * @brief Header de TimerTask.cpp
 * @version 1.0
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TIMERTASK_H
#define TIMERTASK_H

#ifdef ARDUINO
  #if (ARDUINO >= 100)
  #include <Arduino.h>
  #else
  #include <WProgram.h>
  #include <pins_arduino.h>
  #endif
#endif
#include "DynList.h"

#define CYCLIC       false
#define ONETICK    true
#define __refreshTimers__()         TimerTask::refreshTimers()
#define __timers__                  TimerTask::refList
#define __runTask__(isBusy)         { isBusy = true;  task(); isBusy = false; }

typedef bool TimerType;
typedef void (*TaskPtr)(void);

class TimerTask
{
    public:
        TimerTask(uint32_t timeInterval, TimerType timerType, TaskPtr timerTask);
        TimerTask(uint32_t timeInterval, TimerType timerType);
        TimerTask();
        ~TimerTask();
        void setTimeInterval(uint32_t timeInterval);
        void setTimerType(TimerType timerType);
        void setTask(TaskPtr timerTask);
        TaskPtr getTask();
        void removeTask();
        void start();
        void stop();
        void tick();
        bool isRunning();
        bool isBusy();
        static void refreshTimers();
        static DynList<TimerTask*> refList;

    private:
        uint32_t    interval = 0,
                    previousMillis = 0;
        bool        isActive = false,
                    taskIsBusy = false;
        TimerType   type = CYCLIC;
        TaskPtr     task = nullptr;
       
};

#endif