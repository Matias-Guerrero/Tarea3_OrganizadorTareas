#ifndef STRUCT.H
#define STRUCT.H

#define MAXCHAR 100

typedef struct {
    char nombreTarea[MAXCHAR];
    int prioridad;
    char tareaPrecedente[MAXCHAR];
} Tarea;

#endif /*   STRUCT.H   */