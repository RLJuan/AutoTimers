# AutoTimers

## Introducción
Librería que permite la automatización de tareas mediante temporizadores por software. Sus principales características son:

- Creación de tareas temporizadas cíclicas o de un solo uso (CYCLIC/ONETICK).
- El refresco de los temporizadores es automático, por lo que no es necesario refrescarlos en el bucle principal (bucle 'loop()').
- Se permite utilizar la función 'delay()', pero sólo es recomendable en una sola tarea (por ejemplo, en el bucle 'loop()'), ya que al tratarse de una función de recuento en un único hilo, su ejecución en más de una tarea (coincidiendo en el tiempo), provocará que se procese principalmente el último 'delay()', dejando los demás en cola.
- La librería proporciona una ejecución multitarea emulada. Es decir, siempre y cuando no se bloquee ninguna de las tareas (incluido el bucle principal 'loop()') mediante un bucle infinito o una petición excesivamente larga, puede interpretarse que el proceso es "multihilo".

## Librerías auxiliares
Para el correcto funcionamiento de AutoTimers se incluye las siguientes librerías escritas por el autor:

- TimerTask (.h|.cpp): proporciona la clase para la implementación de temporizadores por software. Es el corazón de AutoTimers.
- DynList.h: permite crear listas dinámicas. A diferencia de los arrays, su tamaño no es estático. Se usa para el auto-refresco de los temporizadores.
- GhostThread.h: permite ejecutar código de forma oculta en el bucle principal ('loop()'). Además redefine la función 'delay()' para poder ejecutar código mientras se llevan a cabo los retrasos. Se usa para el auto-refresco de los temporizadores.

## Autor
[@RLJuan](https://github.com/RLJuan)
