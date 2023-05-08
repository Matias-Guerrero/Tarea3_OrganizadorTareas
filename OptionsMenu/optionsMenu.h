#ifndef optionsMenu_h
#define optionsMenu_h

#include "../TreeMap/treemap.h"
#include "../Map/Map.h"

// Aca se prototipan las funciones que se van a usar en el main

void mostrarMenu();

void ingresarValor(char *valor, char *mensaje);

void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea);

#endif /*   optionsMenu_h   */