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
    puts("2. Establecer precedencia entre tareas"); 
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

void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente)
{
    // Verificar que ambas tareas existan
    if(searchMap(mapaTareas, nombreTarea) != NULL && searchMap(mapaTareas, nombreTareaPrecedente) != NULL)
    {
        // Buscar tarea en el arbol
        Pair *parActual = firstTreeMap(arbolTareas);

        // Recorrer el arbol hasta encontrar la tarea
        while(parActual != NULL)
        {
            // Obtener tarea actual
            Tarea *tareaActual = (Tarea *)parActual->value;

            // Verificar si la tarea actual es la que se busca
            if(strcmp(tareaActual->nombreTarea, nombreTarea) == 0)
            {
                // Asignar tarea precedente
                strcpy(tareaActual->tareaPrecedente, nombreTareaPrecedente);

                // Actualizar tarea en el arbol
                actualizarNodoActual(arbolTareas, (void *)tareaActual->prioridad, (void *)tareaActual);

                system("cls");
                // Mostrar mensaje de exito
                puts("\n========================================");
                printf(" Se establece que la tarea %s\n", tareaActual->nombreTarea); 
                printf(" tiene como precedente a la tarea %s\n",  tareaActual->tareaPrecedente);
                puts("========================================\n");
                break;
            }

            // Obtener siguiente tarea
            parActual = nextTreeMap(arbolTareas);
        }

    }
    else
    {
        system("cls");

        // Mostrar mensaje de error
        puts("\n========================================");
        puts("    La tarea o el precedente no existe");
        puts("========================================\n");
    }
    
    system("pause");
    
}