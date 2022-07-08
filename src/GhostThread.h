/**
 * @file GhostThread.h
 * @author Juan R. López (sfcduino@gmail.com)
 * @brief "Sé que esta librería merece la muerte. Sorry por crearla." Juan R. López.
 * @version 1.0
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GHOSTTHREAD_H
#define GHOSTTHREAD_H

#ifndef USE_ORIGINAL_LOOP

#define __oldLoop__() loop()
#define __serialEvents__() \
if(serialEventRun) serialEventRun();
#define __runLoop__(isBusy) \
{ isBusy = true; loop_(); isBusy = false; }
#define doThreads() \
{ __newLoop__(); __threads__(); __serialEvents__(); }

void loop_();
void __newLoop__();
void delay_(uint32_t t_ms);
inline void __threads__();

void __oldLoop__() { __newLoop__(); __threads__(); }
void __newLoop__()
{
    static bool isBusy = false;
    if(isBusy) return;
    __runLoop__(isBusy);
}

#define loop()      loop_()
#define delay(t_ms) delay_(t_ms)
#define REFRESHTHREADS_AFTERLOOP() inline __threads__()

void delay(uint32_t t_ms)
{
    if(t_ms == 0) return;
    uint32_t previousMillis = millis();
    while((millis() - previousMillis) < t_ms) doThreads();
}

#endif //USE_ORIGINAL_LOOP

#endif