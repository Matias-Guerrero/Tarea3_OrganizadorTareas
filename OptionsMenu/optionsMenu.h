#ifndef optionsMenu_h
#define optionsMenu_h

#include "../TreeMap/treemap.h"
#include "../Map/Map.h"

//===================================================================================================
// FUNCIONES HERRAMIENTAS
//===================================================================================================

void mostrarMenu();

void ingresarValor(char *valor, char *mensaje);

//===================================================================================================
// OPCION 1: AGREGAR TAREA
//===================================================================================================

void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea);

//===================================================================================================
// OPCION 2: ESTABLECER PRECEDENCIA
//===================================================================================================

void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente);

//===================================================================================================
// OPCION 3: MOSTRAR TAREAS POR HACER
//===================================================================================================

void mostrarTareasPorHacer(TreeMap *arbolTareas, Map *mapaTareas);

//===================================================================================================
// OPCION 4: MOSTRAR TAREAS POR HACER
//===================================================================================================

void marcarTareaCompletada(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea);

//===================================================================================================
// OTRAS FUNCIONES
//===================================================================================================

void recorrerArbolyMapa(TreeMap *arbolTareas, Map *mapaTareas);

#endif /*   optionsMenu_h   */