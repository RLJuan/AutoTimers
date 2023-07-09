#include "AutoTimers.h"

TimerTask timers[4];

void setup()
{
  Serial.begin(9600);
  timers[0].setTimeInterval(1000);
  timers[1].setTimeInterval(2000);
  timers[2].setTimeInterval(3000);
  timers[3].setTimeInterval(4000);
  
  timers[0].setTask(task0);
  timers[1].setTask(task1);
  timers[2].setTask(task2);
  timers[3].setTask(task3);
  
  timers[0].start();
  timers[1].start();
  timers[2].start();
  timers[3].start();
}

void loop()
{
  Serial.println("Loop");
  delay(5000);
}

void task0()
{
  Serial.println("T0");
}

void task1()
{
  Serial.println("T1");
}

void task2()
{
  Serial.println("T2");
}

void task3()
{
  Serial.println("T3");
}
