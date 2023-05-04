#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "Struct/struct.h"
#include "List/list.h"
#include "TreeMap/treemap.h"
#include "OptionsMenu/optionsMenu.h"

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if((int)key1 < (int)key2) return 1;
    return 0;
}


int main(int argc, const char * argv[])
{
    int opcion;

    TreeMap* tareas = createTreeMap(lower_than_int);

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
        //mostrarMenu();
        puts("");
        printf("Ingrese la opcion que desea realizar: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch (opcion)
        {
            case 1:
                system("cls");
                
                break;

            case 2:
                system("cls");
                
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

                break;  
            
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");
        }
    } while (opcion != 7);


 
    return EXIT_SUCCESS;
}