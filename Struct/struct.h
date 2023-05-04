#ifndef STRUCT_h
#define STRUCT_h

#define MAXCHAR 100

typedef struct {
    char nombreTarea[MAXCHAR];
    int prioridad;
    char tareaPrecedente[MAXCHAR];
} Tarea;

#endif /*   STRUCT_h   */