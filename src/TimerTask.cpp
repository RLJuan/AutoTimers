/**
 * @file TimerTask.cpp
 * @author Juan R. López (sfcduino@gmail.com)
 * @brief Permite crear tareas temporizadas.
 * @version 1.0
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TimerTask.h"
#include "DynList.h"

/**
 * @brief   Lista de referencias. Permite acceder a todos los temporizadores
 * creados previamente.
 * #### Puede utilizarse para implementar otro método de refresco.
 * 
 */
DynList<TimerTask*> TimerTask::refList;

/**
 * @brief Construye un nuevo objeto TimerTask.
 * 
 * @param timeInterval Intervalo de tiempo del temporizador.
 * @param timerType Tipo de temporizador:
 * - CYCLIC: El temporizador ejecuta la tarea de forma cíclica.
 * - ONETICK: El temporizador solo ejecuta la tarea una vez y
 * finaliza su ejecución.
 * @param timerTask Tarea (función) que se ejecutará una vez cumplido el
 * invervalo de tiempo configurado (timeInterval).
 */

TimerTask::TimerTask(uint32_t timeInterval, TimerType timerType, TaskPtr timerTask)
{
    interval = timeInterval;
    type = timerType;
    task = timerTask;
    refList.Add(this);
}

/**
 * @brief Construye un nuevo objeto TimerTask.
 * 
 * @param timeInterval Intervalo de tiempo del temporizador.
 * @param timerType Tipo de temporizador:
 * - CYCLIC: El temporizador ejecuta la tarea de forma cíclica.
 * - ONETICK: El temporizador solo ejecuta la tarea una vez y
 * finaliza su ejecución.
 */

TimerTask::TimerTask(uint32_t timeInterval, TimerType timerType)
{
    interval = timeInterval;
    type = timerType;
    refList.Add(this);
}

/**
 * @brief Construye un nuevo objeto TimerTask.
 * 
 */

TimerTask::TimerTask()
{
    refList.Add(this);
}

/**
 * @brief Destruye un el objeto TimerTask.
 * 
 */

TimerTask::~TimerTask()
{ 
    this->removeTask();
    refList.RemoveFirst(this);
}

/**
 * @brief Configura/modifica el intervalo de tiempo.
 * 
 * @param timeInterval Intervalo de tiempo del temporizador.
 */

void TimerTask::setTimeInterval(uint32_t timeInterval)
{
    interval = timeInterval;
}

/**
 * @brief Configura/modifica el tipo de temporizador (CYCLIC / ONETICK).
 * 
 * @param timerType Tipo de temporizador:
 * - CYCLIC: El temporizador ejecuta la tarea de forma cíclica.
 * - ONETICK: El temporizador solo ejecuta la tarea una vez y
 * finaliza su ejecución.
 */

void TimerTask::setTimerType(TimerType timerType)
{
    type = timerType;
}

/**
 * @brief Configura/modifica la tarea a realizar.
 * 
 * @param timerTask Tarea (función)
 */

void TimerTask::setTask(void (*timerTask)(void))
{
    task = timerTask; 
}

/**
 * @brief Devuelve la tarea.
 * 
 */

TaskPtr TimerTask::getTask()
{
    return task;
}

/**
 * @brief Elimina la tarea previamente configurada.
 * 
 */

void TimerTask::removeTask()
{
    task = nullptr;
}

/**
 * @brief Arranca el temporizador (empieza a correr).
 * 
 */

void TimerTask::start()
{
    isActive = true;
    previousMillis = millis();
}

/**
 * @brief Para el temporizador.
 * 
 */

void TimerTask::stop()
{
    isActive = false;
}

/**
 * @brief Devuelve 'true' si el temporizador está corriendo.
 * 
 */

bool TimerTask::isRunning()
{
    return isActive;
}

/**
 * @brief Devuelve 'true' si la tarea está ocupada.
 * 
 */

bool TimerTask::isBusy()
{
    return taskIsBusy;
}

/**
 * @brief Actualiza todos los temporizadores.
 * En esta versión, GhostThread se encarga de refrescar los temporizadores,
 * por lo que no es necesario el uso de este método.
 */

void TimerTask::refreshTimers()
{
    for(size_t i = 0; i < refList.Size(); i++) refList[i]->tick();
}

/**
 * @brief Actualiza el temporizador.
 * En esta versión, GhostThread se encarga de refrescar los temporizadores,
 * por lo que no es necesario el uso de este método.
 * #### Puede utilizarse para implementar otro método de refresco.
 */

void TimerTask::tick()
{
    if (taskIsBusy) { previousMillis = millis(); return; }
    if (isActive && (interval == 0 || (millis() - previousMillis) >= interval))
	{
        if (type == ONETICK) this->stop();
        else previousMillis = millis();
        if (task != nullptr) __runTask__(taskIsBusy);
	}
}
