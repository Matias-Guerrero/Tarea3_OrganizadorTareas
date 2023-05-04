#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "optionsMenu.h"
#include "../Struct/struct.h"
#include "../List/list.h"
#include "../TreeMap/treemap.h"

// Aca se definen las funciones que se van a usar en el main

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