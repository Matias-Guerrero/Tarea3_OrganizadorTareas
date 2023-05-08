#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "optionsMenu.h"
#include "../Struct/struct.h"
#include "../List/list.h"
#include "../TreeMap/treemap.h"
#include "../Map/map.h"

// Aca se definen las funciones que se van a usar en el main

void mostrarMenu()
{
    puts("=======================================================");
    puts("     Menu: Organizador de tareas");
    puts("=======================================================");
    puts("1. Agregar tarea");
    puts("2. Establecer precedencia entre tareas"); // Sin implementar
    puts("3. Mostrar tareas por hacer"); // Sin implementar
    puts("4. Marcar tarea como completada"); // Sin implementar
    puts("5. Deshacer ultima accion"); // Sin implementar
    puts("6. Cargar datos de tareas desde un archivo de texto"); // Sin implementar
    puts("7. Salir");
    puts("=======================================================");
}

void ingresarValor(char *valor, char *mensaje)
{
    puts("========================================");
    printf("%s:\n", mensaje);
    puts("========================================");
    scanf("%30[^\n]", valor);
    while(getchar() != '\n');
}

void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea)
{
    if(searchMap(mapaTareas, nombreTarea) == NULL)
    {
        // Crear tarea
        Tarea *tarea = (Tarea*) malloc(sizeof(Tarea));

        // Asignar valores a la tarea
        strcpy(tarea->nombreTarea, nombreTarea);
        tarea->prioridad = prioridadTarea;
        strcpy(tarea->tareaPrecedente, "");

        // Agregar tarea al arbol y al mapa
        insertTreeMap(arbolTareas, (void *)tarea->prioridad, (void *)tarea);
        insertMap(mapaTareas, tarea->nombreTarea, tarea);

        system("cls");

        // Mostrar mensaje de exito
        puts("\n========================================");
        puts("        Tarea agregada exitosamente");
        puts("========================================\n");
    }
    else
    {
        // Mostrar mensaje de error
        puts("\n========================================");
        puts("          La tarea ya existe");
        puts("========================================\n");
    }

    system("pause");
}