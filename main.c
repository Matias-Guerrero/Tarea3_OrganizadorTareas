#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "Struct/struct.h"
#include "List/list.h"
#include "TreeMap/treemap.h"

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

 
    return EXIT_SUCCESS;
}