#ifndef STRUCT_h
#define STRUCT_h

#include "../List/list.h" // revisar si es necesario

#define MAXCHAR 100

//==============================================================================
// Aca definimos las estructuras que vamos a utilizar en el programa
//==============================================================================


// Estructura para almacenar las tareas
typedef struct {
    char nombreTarea[MAXCHAR];
    int prioridad;
    List* tareasPrecedentes;
} Tarea;

// Estructura para pila de acciones
typedef struct {
    char nombreAccion[MAXCHAR];
    void* datoAccion;
} Accion;

#endif /*   STRUCT_h   */