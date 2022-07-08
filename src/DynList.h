/**
 * @file DynList.h
 * @author Juan R. López (sfcduino@gmail.com)
 * @brief Permite crear listas dinámicas.
 * @version 1.0
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DYNLIST_H
#define DYNLIST_H

template <typename T>
class DynList
{
    public:
        DynList();
        ~DynList();
        T& operator[](const size_t index);
        size_t Size();
        void Add(T item);
        size_t IndexOf(T item);
        void RemoveFirst(T item);
    private:
        size_t size = 0;
        T* items = NULL; /* posterior alloc */
};

template <typename T>
DynList<T>::DynList(){}

template <typename T>
DynList<T>::~DynList()
{
    /* si 'items' nunca se ha asignado o ya ha sido liberado, no hay nada que liberar */
    if(items != NULL) free(items);
}

template <typename T>
T& DynList<T>::operator[](const size_t index)
{
    return items[index];
}

template <typename T>
size_t DynList<T>::Size() { return size; }

template <typename T>
void DynList<T>::Add(T item)
{
    size_t newSize = size + 1;
    /* si 'items' nunca se ha asignado o ya ha sido liberado, 'realloc' funciona como 'malloc' */
    items = (T*) realloc(items, newSize * sizeof(T));
    items[size] = item;
    size = newSize;
}

template <typename T>
size_t DynList<T>::IndexOf(T item)
{
    size_t index;
    for(index = 0; index < size && items[index] != item; index++);
    return index; /* si no existe, devuelve el valor de 'size' (= 'index' + 1 -> indice fuera de rango) */
}

template <typename T>
void DynList<T>::RemoveFirst(T item)
{
	if (size <= 0) return; /* si no hay nada, retorna */
	
	size_t index = this->IndexOf(item);
	if (index >= size) return; /* si no existe, retorna */
	
    size_t newSize = size - 1;
    if (newSize > 0 )
    {
        for(size_t i = index; i < newSize; i++) items[i] = items[i+1];
        items = (T*) realloc(items, newSize * sizeof(T));
    }
    else
    { 
        free(items);
        items = NULL;
    }
    size = newSize;
}


#endif