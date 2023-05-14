#!/bin/bash

# Script para compilar el programa desde git bash

# Ingresar el nombre del ejecutable
read -p "Ingrese el nombre del ejecutable: " executable

# Archivos a compilar
FILES="main.c  Struct/struct.h List/list.c TreeMap/treemap.c Map/Map.c OptionsMenu/optionsMenu.c Stack/stack.h"

# Compilacion con gcc
gcc -g $FILES -o $executable

# Verificar si hubo errores
if [ $? -eq 0 ]; then
    echo "Compilacion exitosa"
else
    echo "Hubo errores en la compilacion"
fi

# Ejectuar el programa en una ventana nueva
# cmd.exe /c $executable.exe