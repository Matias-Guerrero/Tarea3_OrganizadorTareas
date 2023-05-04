#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "Struct/struct.h"
#include "List/list.h"
#include "TreeMap/treemap.h"

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
    int opcion;
    Tarea* tarea;

    TreeMap* tareas = createTreeMap(is_equal_string);





    return EXIT_SUCCESS;
}