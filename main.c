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
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch (opcion)
        {
            case 1:
                system("cls");
               
                // Pedir nombre de la tarea
                ingresarValor(nombreTarea, "    Ingrese el nombre de la tarea");

                // Pedir prioridad de la tarea|
                ingresarValor(auxiliar, "    Ingrese la prioridad de la tarea");
                prioridadTarea = atoi(auxiliar);

                // Se llama a la funcion agregarTarea
                agregarTarea(arbolTareas, mapaTareas, nombreTarea, prioridadTarea);
                
                break;

            case 2:
                system("cls");

                puts("========================================");
                puts("  Establecer precedencia entre tareas");   
                puts("========================================\n");
                
                // Pedir nombre de la tarea 1
                ingresarValor(auxiliar, "     Ingrese nombre de tarea 1");

                // Pedir nombre de la tarea 2
                ingresarValor(nombreTarea, "    Ingrese nombre de tarea 2 " );
                
                // Se llama a la funcion establecerPrecedencia
                establecerPrecedencia(arbolTareas, mapaTareas, nombreTarea, auxiliar);
                
                break;

            case 3: 
                system("cls");
                
                break;  

            case 4:
                system("cls");
                
                break;
            
            case 5:
                system("cls");
                
                break;
            
            case 6:
                system("cls");

                break;

            case 7:
                system("cls");
                puts("Gracias por usar el programa :) Hasta luego!");
                sleep(2);
                break;  
            
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");
        }
    } while (opcion != 7);


 
    return EXIT_SUCCESS;
}