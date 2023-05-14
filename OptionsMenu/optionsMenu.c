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

// Funcion para buscar en una lista
bool buscarEnLista(List *lista, char *nombreTarea)
{
    // Buscar tarea en la lista
    Tarea *tareaActual = firstList(lista);

    while(tareaActual != NULL)
    {
        // Verificar si la tarea actual es la que se busca
        if(strcmp(tareaActual->nombreTarea, nombreTarea) == 0)
        {
            return true;
        }

        // Obtener siguiente tarea
        tareaActual = nextList(lista);
    }

    return false;
}

// Funcion para mostrar el menu
void mostrarMenu()
{
    puts("=======================================================");
    puts("     Menu: Organizador de tareas");
    puts("=======================================================");
    puts("1. Agregar tarea");
    puts("2. Establecer precedencia entre tareas"); 
    puts("3. Mostrar tareas por hacer");
    puts("4. Marcar tarea como completada"); // Sin implementar
    puts("5. Deshacer ultima accion"); // Sin implementar
    puts("6. Cargar datos de tareas desde un archivo de texto"); // Sin implementar
    puts("7. Salir");
    puts("=======================================================");
}

// Funcion para ingresar un valor
void ingresarValor(char *valor, char *mensaje)
{
    puts("===========================================");
    printf("%s:\n", mensaje);
    puts("===========================================");
    scanf("%30[^\n]", valor);
    while(getchar() != '\n');
}

// Funcion para agregar una tarea
void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea)
{
    if(searchMap(mapaTareas, nombreTarea) == NULL)
    {
        // Crear tarea
        Tarea *tarea = (Tarea*) malloc(sizeof(Tarea));

        // Asignar valores a la tarea
        strcpy(tarea->nombreTarea, nombreTarea);
        tarea->prioridad = prioridadTarea;
        tarea->tareasPrecedentes = createList();

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

// Funcion para establecer precedencia entre tareas
void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente)
{
    // Verificar que las tareas ingresadas no sean iguales
    if (strcmp(nombreTarea, nombreTareaPrecedente) == 0)
    {
        system("cls");

        // Mostrar mensaje de error
        puts("\n========================================");
        puts("    No se puede establecer precedencia");
        puts("    entre una tarea y si misma");
        puts("========================================\n");

        system("pause");

        return;
    }

    // Verificar que ambas tareas existan
    if (searchMap(mapaTareas, nombreTarea) != NULL && searchMap(mapaTareas, nombreTareaPrecedente) != NULL)
    {
        // Buscar tarea en el arbol
        Pair *current = firstTreeMap(arbolTareas);

        while (current != NULL)
        {
            Tarea *tareaActual = (Tarea *)current->value;

            if (strcmp(tareaActual->nombreTarea, nombreTarea) == 0)
            {
                // Verificar que la tarea precedente no exista en la lista de precedentes
                if (buscarEnLista(tareaActual->tareasPrecedentes, nombreTareaPrecedente))
                {
                    system("cls");

                    // Mostrar mensaje de error
                    puts("\n========================================");
                    puts("    No se puede establecer precedencia");
                    puts("    porque ya existe dicha precedencia");
                    puts("========================================\n");

                    system("pause");

                    return;
                }

                Tarea *tareaPrecedente = searchMap(mapaTareas, nombreTareaPrecedente);

                // Asignar tarea precedente a la lista de precedentes
                pushBack(tareaActual->tareasPrecedentes, tareaPrecedente);

                system("cls");
                
                // Mostrar mensaje de exito
                puts("\n==================================================");
                printf("    Se establecio que => %s\n", tareaActual->nombreTarea);
                printf("    Tiene como precedente => %s\n", nombreTareaPrecedente);
                puts("========================================\n");

                system("pause");

                break;
            }

            // Avanzar al siguiente par en el árbol
            current = nextTreeMap(arbolTareas);
        }
    }
        
}

// Funcion para mostrar tareas precedentes de una tarea
void mostrarTareasPrecedentes(List *tareasPrecedentes)
{
    // Verificar si la lista esta vacia
    if(firstList(tareasPrecedentes) == NULL)
    {
        printf("Sin tareas\n");
        return;
    }

    // Se recorre la lista para mostrar las tareas precedentes
    Tarea* tareaActual = firstList(tareasPrecedentes);

    while(tareaActual != NULL)
    {
        // Mostrar tarea actual
        printf(" %s", tareaActual->nombreTarea);

        // Obtener siguiente tarea
        tareaActual = nextList(tareasPrecedentes);
    }

    printf("\n");
}

// Funcion para guardar las tareas precedentes de una tarea
void guardarTareasPrecedentes(List * listaPrecedentes, List * listaTareasPorHacer)
{
    Tarea *tareaActual = firstList(listaPrecedentes);

    while(tareaActual != NULL)
    {
        // Verificar si la tarea actual no esta en la lista de tareas por hacer
        if(!buscarEnLista(listaTareasPorHacer, tareaActual->nombreTarea))
        {
            // Verificar si la tarea actual tiene tareas precedentes
            if(firstList(tareaActual->tareasPrecedentes) != NULL)
            {
                // Guardar tareas precedentes de la tarea actual
                guardarTareasPrecedentes(tareaActual->tareasPrecedentes, listaTareasPorHacer);
            }

            // Agregar tarea actual a la lista de tareas por hacer
            pushBack(listaTareasPorHacer, tareaActual);
        }

        // Obtener siguiente tarea
        tareaActual = nextList(listaPrecedentes);
    }

}

// Funcion que muestra las tareas por hacer segun su prioridad y la tarea precedente
void mostrarTareasPorHacer(TreeMap *arbolTareas, Map *mapaTareas)
{
    // Se verifica que el arbol no este vacio
    if(firstTreeMap(arbolTareas) == NULL || firstMap(mapaTareas) == NULL)
    {
        system("cls");

        // Mostrar mensaje de error
        puts("\n========================================");
        puts("        No hay tareas por hacer");
        puts("========================================\n");

        system("pause");
        return;
    }
    
    // Se crea una lista para almacenar las tareas por hacer
    List *listaTareasPorHacer = createList();

    // Se recorre el arbol para obtener las tareas por hacer
    Pair *parActual = firstTreeMap(arbolTareas);

    while(parActual != NULL)
    {
        // Obtener tarea actual
        Tarea *tareaActual = (Tarea *)parActual->value;

        // Verificar si la tarea actual esta en la lista de tareas por hacer
        if(!buscarEnLista(listaTareasPorHacer, tareaActual->nombreTarea))
        {
            // Verificar si la tarea actual tiene precedentes
            if(firstList(tareaActual->tareasPrecedentes) != NULL)
            {
                guardarTareasPrecedentes(tareaActual->tareasPrecedentes, listaTareasPorHacer);
            }

            // Se agrega la tarea a la lista de tareas por hacer
            pushBack(listaTareasPorHacer, tareaActual);
        }

        // Avanzar al siguiente par en el árbol
        parActual = nextTreeMap(arbolTareas);
    }

    // Se muestra la lista de tareas por hacer
    Tarea *current = firstList(listaTareasPorHacer);

    system("cls");

    // Mostrar mensaje de exito
    puts("\n=============================================");
    puts("              Tareas por hacer");
    puts("Ordenadas por prioridad y precedencia :");
    puts("=============================================\n");

    // Se crea un contador para mostrar el numero de tareas por hacer
    int contador = 1;

    while(current != NULL)
    {
        printf("%d. %s (Prioridad: %d)",contador , current->nombreTarea, current->prioridad);
        
        if(firstList(current->tareasPrecedentes) != NULL)
        {
            printf(" - Precedente:");
            mostrarTareasPrecedentes(current->tareasPrecedentes);
        }
        else
        {
            printf("\n");
        }

        // Avanzar al siguiente par en el árbol
        current = nextList(listaTareasPorHacer);

        // Aumentar contador
        contador++;
    }

    puts("\n========================================\n");

    system("pause");

    // Se libera la memoria de la lista de tareas por hacer
    free(listaTareasPorHacer);
}

// void marcarTareaCompletada(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea)
// {
//     // Buscar tarea en el mapa
//     Tarea *tareaActual = (Tarea *) searchMap(mapaTareas, nombreTarea);

//     // Se crea un booleano para verificar si se quiere marcar como completada una tarea
//     bool marcarTarea = true;

//     // Verificar si la tarea existe
//     if(tareaActual != NULL)
//     {
//         // Buscar si la tarea a eliminar es precedente de otra tarea
//         Pair *parActual = firstTreeMap(arbolTareas);

//         // Se recorre el arbol para verificar si la tarea a eliminar es precedente de otra tarea
//         while(parActual != NULL)
//         {
//             // Obtener tarea actual
//             Tarea *tareaConPrecedente = (Tarea *)parActual->value;

//             // Verificar si la tarea actual tiene relacion de precedencia con la tarea a eliminar
//             if(strcmp(tareaConPrecedente->tareaPrecedente, nombreTarea) == 0)
//             {
//                 // Se muestra una advertencia
//                 puts("\nEstas seguro que desea eliminar la tarea (S/N) " );
//                 char respuesta[2];
//                 scanf("%s", respuesta);
//                 while(getchar() != '\n');

//                 // Se verifica la respuesta
//                 if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
//                 {
//                     // Se actualiza la tarea con precedente para que no tenga relacion con la tarea a eliminar
//                     strcpy(tareaConPrecedente->tareaPrecedente, "");

//                     // Se actualiza la tarea en el mapa
//                     insertMap(mapaTareas, tareaConPrecedente->nombreTarea, tareaConPrecedente);

//                     // Se actualiza la tarea en el arbol
//                     actualizarNodoActual(arbolTareas, (void *)tareaConPrecedente->nombreTarea, (void *)tareaConPrecedente);

//                 }
//                 else if(strcmp(respuesta, "N") == 0  || strcmp(respuesta, "n") == 0) // Se verifica la respuesta
//                 {
//                     // Se cambia el valor del booleano
//                     marcarTarea = false;
//                 }
//             }
//             // Obtener siguiente tarea
//             parActual = nextTreeMap(arbolTareas);
//         }
        
//         // Verificar si se quiere marcar la tarea como completada
//         if(marcarTarea)
//         {
//             // Se elimina la tarea del mapa
//             eraseMap(mapaTareas, nombreTarea);

//             // Buscar la tarea a eliminar en el arbol
//             parActual = firstTreeMap(arbolTareas);

//             // Se recorre el arbol para eliminar la tarea
//             while(parActual != NULL)
//             {
//                 // Obtener tarea actual
//                 Tarea *tareaActual = (Tarea *)parActual->value;

//                 // Verificar si la tarea actual es la que se busca
//                 if(strcmp(tareaActual->nombreTarea, nombreTarea) == 0)
//                 {
//                     // Eliminar tarea del arbol
//                     eraseTreeMapCurrent(arbolTareas);
//                     break;
//                 }

//                 // Obtener siguiente tarea
//                 parActual = nextTreeMap(arbolTareas);
//             }

//             // Mostrar mensaje de exito
//             puts("\n========================================");
//             printf("        Tarea %s completada\n", nombreTarea);
//             puts("========================================\n");

//         }
        
//     }
//     else
//     {
//         system("cls");

//         // Mostrar mensaje de error
//         puts("\n========================================");
//         puts("        La tarea no existe");
//         puts("========================================\n");
//     }

//     system("pause");
// }

//====================================================================================================
// Funcion Utilizada para rootear el codigo
//====================================================================================================

// Funcion para recorrer el arbol y mostrar el contenido
void recorrerArbolyMapa(TreeMap *arbolTareas, Map *mapaTareas)
{   
    // Obtener raiz del arbol
    Pair *parRaiz = obtenerNodoRaiz(arbolTareas);

    // Si el arbol esta vacio, mostrar mensaje
    if(parRaiz == NULL && firstMap(mapaTareas) == NULL)
    {
        puts("\n========================================");
        puts("      El arbol y el mapa estan vacios");
        puts("========================================");
        return;
    }

    // Mostar tarea raiz
    Tarea *tareaRaiz = (Tarea *)parRaiz->value;

    puts("\n========================================");
    puts("Tarea raiz:");
    printf("Tarea: %s\n", tareaRaiz->nombreTarea);
    printf("Prioridad: %d\n", tareaRaiz->prioridad);
    printf("Tareas precedentes: ");
    mostrarTareasPrecedentes(tareaRaiz->tareasPrecedentes);
    puts("========================================");


    // Buscar tarea en el arbol
    Pair *parActual = firstTreeMap(arbolTareas);

    puts("\n========================================");
    puts("          Tareas Arbol Binario");
    puts("========================================");

    // Recorrer el arbol hasta encontrar la tarea
    while(parActual != NULL)
    {
        // Obtener tarea actual
        Tarea *tareaActual = (Tarea *)parActual->value;

        // Mostrar tarea actual
        printf("Tarea: %s\n", tareaActual->nombreTarea);
        printf("Prioridad: %d\n", tareaActual->prioridad);
        printf("Tareas precedentes: \n");
        mostrarTareasPrecedentes(tareaActual->tareasPrecedentes);
        puts("========================================");

        // Obtener siguiente tarea
        parActual = nextTreeMap(arbolTareas);
    }

    puts("\n========================================");
    puts("          Tareas Mapa");
    puts("========================================");

    // Buscar tarea en el mapa
    Tarea *tareaActual = (Tarea *) firstMap(mapaTareas);

    puts("\n========================================");

    while(tareaActual != NULL)
    {
        // Mostrar tarea actual
        printf("Tarea: %s\n", tareaActual->nombreTarea);
        printf("Prioridad: %d\n", tareaActual->prioridad);
        printf("Tareas precedentes: \n");
        mostrarTareasPrecedentes(tareaActual->tareasPrecedentes);
        puts("========================================");

        // Obtener siguiente tarea
        tareaActual = (Tarea *) nextMap(mapaTareas);
    }
}

//====================================================================================================
//====================================================================================================