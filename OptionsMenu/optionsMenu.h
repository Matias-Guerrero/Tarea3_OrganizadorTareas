#ifndef optionsMenu_h
#define optionsMenu_h

#include "../TreeMap/treemap.h"
#include "../Map/Map.h"

// Aca se prototipan las funciones que se van a usar en el main

void mostrarMenu();

void ingresarValor(char *valor, char *mensaje);

void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea);

void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente);

void mostrarTareasPorHacer(TreeMap *arbolTareas, Map *mapaTareas);

void marcarTareaCompletada(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea);

// Funcion para rootear codigo
void recorrerArbolyMapa(TreeMap *arbolTareas, Map *mapaTareas);

#endif /*   optionsMenu_h   */