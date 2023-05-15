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
#include "../Stack/stack.h"

//===================================================================================================
// FUNCIONES HERRAMIENTAS
//===================================================================================================

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
    puts("4. Marcar tarea como completada"); 
    puts("5. Deshacer ultima accion");
    puts("6. Cargar datos de tareas desde un archivo de texto"); 
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

//===================================================================================================
// OPCION 1: AGREGAR TAREA
//===================================================================================================

// Funcion para agregar una tarea
void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea, Stack *pilaAcciones)
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

        // Creamos la accion para agregar a la pila de acciones
        Accion *accion = (Accion *) malloc(sizeof(Accion));
        strcpy(accion->nombreAccion, "AgregarTarea");
        accion->datoAccion = tarea;

        stack_push(pilaAcciones, accion); // Agregamos la accion a la pila de acciones

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

//===================================================================================================
// OPCION 2: ESTABLECER PRECEDENCIA ENTRE TAREAS
//===================================================================================================

// Funcion para establecer precedencia entre tareas
void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente, Stack *pilaAcciones)
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
        // Buscar tarea en el mapa
        Tarea *tareaActual = searchMap(mapaTareas, nombreTarea);

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

        // Creamos la accion para agregar a la pila de acciones
        Accion *accion = (Accion *) malloc(sizeof(Accion));
        strcpy(accion->nombreAccion, "establecerPrecedencia");
        accion->datoAccion = tareaActual;

        stack_push(pilaAcciones, accion); // Agregamos la accion a la pila de acciones

        // Asignar tarea precedente a la lista de precedentes
        pushBack(tareaActual->tareasPrecedentes, tareaPrecedente);

        system("cls");
        
        // Mostrar mensaje de exito
        puts("\n==================================================");
        printf("    Se establecio que => %s\n", tareaActual->nombreTarea);
        printf("    Tiene como precedente => %s\n", nombreTareaPrecedente);
        puts("========================================\n");

        system("pause");
    }
        
}

//===================================================================================================
// OPCION 3: MOSTRAR TAREAS POR HACER
//===================================================================================================

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

//===================================================================================================
// OPCION 4: MARCAR TAREA COMO COMPLETADA
//===================================================================================================

void marcarTareaCompletada(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, Stack *pilaAcciones)
{
    // Buscar tarea en el mapa
    Tarea *tareaActual = (Tarea *) searchMap(mapaTareas, nombreTarea);

    // Booleano para ver si existe relacion de precedencia
    bool precedencia = false;

    // Respuesta del usuario
    char respuesta[2];

    // Se crea una lista para almacenar de donde es precedente la tarea a eliminar
    List *listaPrecedentesEliminados = createList();

    // Verificar si la tarea existe
    if(tareaActual != NULL)
    {
        // Buscar si la tarea a eliminar es precedente de otra tarea
        Pair *parActual = firstTreeMap(arbolTareas);

        // Se recorre el arbol para verificar si la tarea a eliminar es precedente de otra tarea
        while(parActual != NULL)
        {
            // Obtener tarea actual
            Tarea *tareaActual = (Tarea *)parActual->value;

            // Verificar si la tarea actual tiene tareas precedentes
            if(firstList(tareaActual->tareasPrecedentes) != NULL)
            {
                // Buscar tarea actual en la lista de tareas precedentes
                Tarea *tareaPrecedente = firstList(tareaActual->tareasPrecedentes);

                while(tareaPrecedente != NULL)
                {
                    // Verificar si la tarea actual es precedente de la tarea a eliminar
                    if(strcmp(tareaPrecedente->nombreTarea, nombreTarea) == 0)
                    {
                        if(precedencia == false)
                        {
                            // Se muestra una advertencia
                            puts("\nEstas seguro que desea eliminar la tarea (S/N) " );
                            scanf("%s", respuesta);
                            while(getchar() != '\n');
                        }

                        // Se verifica la respuesta
                        if(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
                        {
                            // Se crea un puntero a Tarea en cada iteracion
                            Tarea *tareaConPrecedente = (Tarea *)malloc(sizeof(Tarea));

                            // Se copia la tarea actual en el puntero
                            memcpy(tareaConPrecedente, tareaActual, sizeof(Tarea));

                            // Se agrega la tarea a la lista de precedentes eliminados
                            pushBack(listaPrecedentesEliminados, tareaConPrecedente);

                            // Se elimina la tarea de la lista de precedentes
                            popCurrent(tareaActual->tareasPrecedentes);

                            precedencia = true;

                        }
                        else if(strcmp(respuesta, "N") == 0 || strcmp(respuesta, "n") == 0) // Se verifica la respuesta
                        {
                            // Mensaje indicado que no se elimino la tarea
                            puts("\n===============================");
                            puts("    No se elimino la tarea");
                            puts("===============================");

                            system("pause");

                            return;
                        }
                        
                    }

                    // Obtener siguiente tarea
                    tareaPrecedente = nextList(tareaActual->tareasPrecedentes);
                }
            }

            // Avanzar al siguiente par en el árbol
            parActual = nextTreeMap(arbolTareas);
        }

        // Se elimina la tarea del mapa
        eraseMap(mapaTareas, nombreTarea);

        // Recorrer el arbol para eliminar la tarea
        parActual = firstTreeMap(arbolTareas);

        while(parActual != NULL)
        {
            // Obtener tarea actual
            Tarea *tareaActual = (Tarea *)parActual->value;

            // Verificar si la tarea actual es la tarea a eliminar
            if(strcmp(tareaActual->nombreTarea, nombreTarea) == 0)
            {
                // Se elimina la tarea del arbol
                eraseTreeMapCurrent(arbolTareas);

                // Creamos la accion para agregar a la pila de acciones
                Accion *accionActual = (Accion *)malloc(sizeof(Accion));
                strcpy(accionActual->nombreAccion, "marcarTareaCompletada");

                // Se agregar la tarea a la lista de tareas eliminadas
                pushFront(listaPrecedentesEliminados, tareaActual);

                accionActual->datoAccion = listaPrecedentesEliminados;

                stack_push(pilaAcciones, accionActual); // Se agrega la accion a la pila de acciones

                break;
            }
            
            // Avanzar al siguiente par en el árbol
            parActual = nextTreeMap(arbolTareas);
        }

        // Se muestra un mensaje de exito
        puts("\n========================================");
        puts("        Tarea completada con exito");
        puts("========================================\n");

        system("pause");
    }
    else
    {
        // Se muestra un mensaje de error
        puts("\n========================================");
        puts("        La tarea no existe");
        puts("========================================\n");

        system("pause");
    }
}

//===================================================================================================
// OPCION 5: DESHACER ULTIMA ACCION
//===================================================================================================

void deshacerAccion(TreeMap *arbolTareas, Map *mapaTareas, Stack *pilaAcciones)
{
    // Se obtiene la accion actual
    Accion *ultimaAccion = (Accion *)stack_top(pilaAcciones);

    // Se verifica si la pila de acciones esta vacia
    if(ultimaAccion == NULL)
    {
        // Se muestra un mensaje de error
        puts("\n========================================");
        puts("        No hay acciones para deshacer");
        puts("========================================\n");

        system("pause");

        return;
    }

    // Se verifica si la ultima accion fue agregar tarea
    if(strcmp(ultimaAccion->nombreAccion, "AgregarTarea") == 0)
    {
        // Se elimina la accion de la pila
        stack_pop(pilaAcciones);

        // Se obtiene la tarea a eliminar
        Tarea *tareaActual = (Tarea *)ultimaAccion->datoAccion;

        // Se elimina la tarea del mapa
        eraseMap(mapaTareas, tareaActual->nombreTarea);

        // Recorrer el arbol para eliminar la tarea
        Pair *parActual = firstTreeMap(arbolTareas);

        while(parActual != NULL)
        {
            // Obtener tarea actual
            Tarea *tareaActualArbol = (Tarea *)parActual->value;

            // Verificar si la tarea actual es la tarea a eliminar
            if(strcmp(tareaActualArbol->nombreTarea, tareaActual->nombreTarea) == 0)
            {
                // Se elimina la tarea del arbol
                eraseTreeMapCurrent(arbolTareas);

                break;
            }

            // Avanzar al siguiente par en el árbol
            parActual = nextTreeMap(arbolTareas);
        }

        // Se muestra un mensaje de exito
        puts("\n========================================");
        puts("        Accion agregarTarea deshecha");
        puts("========================================\n");
    }

    // Se verifica si la ultima accion fue establecer precedencia
    if(strcmp(ultimaAccion->nombreAccion, "establecerPrecedencia") == 0)
    {
        // Se elimina la accion de la pila
        stack_pop(pilaAcciones);

        // Se obtiene la tarea de la accion
        Tarea *tareaActual = (Tarea *)ultimaAccion->datoAccion;

        // Se elimina el ultimo elemento de la lista de precedentes
        popCurrent(tareaActual->tareasPrecedentes);

        // Se muestra un mensaje de exito
        puts("\n========================================");
        puts("  Accion establecerPrecedencia deshecha");
        puts("========================================\n");
    }

    // Se verifica si la ultima accion fue marcar tarea completada
    if(strcmp(ultimaAccion->nombreAccion, "marcarTareaCompletada") == 0)
    {
        // Se elimina la accion de la pila
        stack_pop(pilaAcciones);

        // Se obtiene la lista de tareas precedentes eliminadas
        List *listaPrecedentesEliminados = (List *)ultimaAccion->datoAccion;

        // Se obtiene la tarea eliminada de la primera posicion de la lista
        Tarea *tareaActual = (Tarea *)firstList(listaPrecedentesEliminados);

        // Se agrega la tarea completada al arbol y al mapa
        insertMap(mapaTareas, tareaActual->nombreTarea, tareaActual);
        insertTreeMap(arbolTareas, (void *)tareaActual->prioridad, (void *)tareaActual);

        // Se obtiene el nombre de la tarea donde es precedente la tarea eliminada
        Tarea *tareaPrecedenteEliminar = (Tarea *)nextList(listaPrecedentesEliminados);

        // Si la tarea donde es precedente la tarea eliminada no es nula
        while(tareaPrecedenteEliminar != NULL)
        {
            // Buscar la tarea en el mapa
            Tarea *tareaPrecedente = searchMap(mapaTareas, tareaPrecedenteEliminar->nombreTarea);

            // Se agrega la tarea eliminada a la lista de tareas precedentes de la tarea donde es precedente
            pushBack(tareaPrecedente->tareasPrecedentes, tareaActual->nombreTarea);

            // Se avanza al siguiente elemento de la lista
            tareaPrecedenteEliminar = nextList(listaPrecedentesEliminados);
        }

        // Se muestra un mensaje de exito
        puts("\n========================================");
        puts("  Accion marcarTareaCompletada deshecha");
        puts("========================================\n");
    }

    system("pause");
}

//===================================================================================================
// OPCION 6: CARGAR TAREAS
//===================================================================================================

void cargarTareas(TreeMap *arbolTareas, Map *mapaTareas, char *nombreArchivo)
{
    // Se abre el archivo de tareas
    FILE *archivoTareas = fopen(nombreArchivo, "r");

    // Se verifica si el archivo existe
    if(archivoTareas == NULL)
    {
        // Se muestra un mensaje de error
        puts("\n========================================");
        puts("        El archivo no existe");
        puts("========================================\n");
    }
    else // Si el archivo existe
    {
        char linea[100*MAXCHAR]; // Variable para almacenar la linea leida del archivo
        char *campo;
        char *lineaPrecedentes; // Variable para almacenar la linea de precedentes

        char nombreTarea[MAXCHAR];
        int prioridadTarea; 

        // Se lee la primera linea del archivo
        fgets(linea, 100*MAXCHAR, archivoTareas);

        // Se lee la siguiente linea del archivo
        while(fgets(linea, 100*MAXCHAR, archivoTareas))
        {
            // Se obtiene el nombre de la tarea
            campo = strtok(linea, ",");
            strcpy(nombreTarea, campo);

            // Se obtiene la prioridad de la tarea
            campo = strtok(NULL, ",");
            prioridadTarea = atoi(campo);

            // Se obtienen las precencias de la tarea
            lineaPrecedentes = strtok(NULL, "\n");

            // Se crea una lista para almacenar los precedentes
            List *listaPrecedentes = createList();

            if(lineaPrecedentes != NULL)
            {
                // Se obtiene el primer precedente
                campo = strtok(lineaPrecedentes, " ");

                while (campo != NULL)
                {
                    // Se crea una nueva variable precedente en cada iteración
                    char *precedente = malloc(strlen(campo) + 1);
                    strcpy(precedente, campo);

                    // Se agrega el precedente a la lista
                    pushBack(listaPrecedentes, precedente);

                    // Se obtiene el siguiente precedente
                    campo = strtok(NULL, " ");
                }
            }

            // Se crea la tarea
            Tarea *tarea = (Tarea *)malloc(sizeof(Tarea));
            strcpy(tarea->nombreTarea, nombreTarea);
            tarea->prioridad = prioridadTarea;
            tarea->tareasPrecedentes = listaPrecedentes;

            // Se agrega la tarea al arbol y al mapa
            insertMap(mapaTareas, tarea->nombreTarea, tarea);
            insertTreeMap(arbolTareas, (void *)tarea->prioridad, (void *)tarea);
        }

        // Se muestra un mensaje de exito
        puts("\n========================================");
        puts("     Tareas cargadas exitosamente");
        puts("========================================\n");

        // Se cierra el archivo
        fclose(archivoTareas);

        system("pause");

    }
}


//====================================================================================================
// OTRAS FUNCIONES
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