#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "Struct/struct.h"
#include "List/list.h"
#include "TreeMap/treemap.h"
#include "Map/Map.h"
#include "OptionsMenu/optionsMenu.h"
#include "Stack/stack.h"

//===================================================================================================
// FUNCIONES PARA EL MANEJO DE ARBOL Y MAPA
//===================================================================================================

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if((int)key1 < (int)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

//===================================================================================================
// FUNCION PRINCIPAL
//===================================================================================================

int main(int argc, const char * argv[])
{
    // Declaracion de variables
    int opcion;
    int prioridadTarea;
    char nombreTarea[MAXCHAR];
    char auxiliar[MAXCHAR];

    // Declaracion de estructuras
    TreeMap* arbolTareas = createTreeMap(lower_than_int);
    Map* mapaTareas = createMap(is_equal_string);
    Stack* pilaAcciones = stack_create();

    // Titulo del programa
    system("cls");
    puts("========================================");
    puts("    Tarea 3: Organizador de tareas");
    puts("========================================");
    puts(" Desarrollado por: ");
    puts("    - Matias Guerrero Castillo");
    puts("    - Fabiana Pina Vera");
    puts("========================================");
    sleep(2);

    do
    {
        system("cls");

        // Mostrar menu
        mostrarMenu();
        puts("");

        // Pedir opcion
        printf("Ingrese la opcion que desea realizar: ");
        scanf("%30[^\n]", auxiliar);
        while(getchar() != '\n');

        do
        {
            if(strlen(auxiliar) > 1)
            {
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");

                system("cls");

                // Mostrar menu
                mostrarMenu();
                puts("");

                printf("Ingrese la opcion que desea realizar: ");
                scanf("%30[^\n]", auxiliar);
                while(getchar() != '\n');
            }
        } while(strlen(auxiliar) > 1);

        opcion = atoi(auxiliar);

        switch (opcion)
        {
            case 1:
                system("cls");
               
                // Pedir nombre de la tarea
                ingresarValor(nombreTarea, "    Ingrese el nombre de la tarea");
                puts("");

                // Pedir prioridad de la tarea|
                ingresarValor(auxiliar, "    Ingrese la prioridad de la tarea");
                prioridadTarea = atoi(auxiliar);

                // Se llama a la funcion agregarTarea
                agregarTarea(arbolTareas, mapaTareas, nombreTarea, prioridadTarea, pilaAcciones);
                
                break;

            case 2:
                system("cls");

                puts("========================================");
                puts("  Establecer precedencia entre tareas");   
                puts("========================================\n");
                
                // Pedir nombre de tarea precedente 
                ingresarValor(auxiliar, "   Establecer tarea ");

                puts("");

                // Pedir nombre de tarea a preceder
                ingresarValor(nombreTarea, "    Como precedente de " );
                
                // Se llama a la funcion establecerPrecedencia
                establecerPrecedencia(arbolTareas, mapaTareas, nombreTarea, auxiliar, pilaAcciones);
                
                break;

            case 3: 
                system("cls");

                // Se llama a la funcion mostrarTareasPorHacer
                mostrarTareasPorHacer(arbolTareas, mapaTareas);
                
                break;  

            case 4:
                system("cls");

                // Pedir nombre de la tarea a marcar
                ingresarValor(nombreTarea, "Ingrese el nombre de la tarea a completar");

                marcarTareaCompletada(arbolTareas, mapaTareas, nombreTarea, pilaAcciones);
                
                break;
            
            case 5:
                system("cls");

                // Se llama a la funcion deshacerAccion
                deshacerAccion(arbolTareas, mapaTareas, pilaAcciones);
                
                break;
            
            case 6:
                system("cls");

                //Pedir el nombre del archivo
                ingresarValor(auxiliar, " Ingrese el nombre del archivo");

                // Se llama a la funcion cargarTareas
                cargarTareas(arbolTareas, mapaTareas, auxiliar);

                break;

            case 7:
                system("cls");
                puts("Gracias por usar el programa :) Hasta luego!");
                sleep(2);
                break;

            case 8:
                system("cls");
                recorrerArbolyMapa(arbolTareas, mapaTareas);
                system("pause");
                break;    
            
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");
        }
    } while (opcion != 7);
    
    // Liberar memoria
    free(arbolTareas);
    free(mapaTareas);
    free(pilaAcciones);

    return EXIT_SUCCESS;
}