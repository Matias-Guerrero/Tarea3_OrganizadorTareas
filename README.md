# Tarea3_OrganizadorTareas
Tarea N°3 de Estructura de Datos, Ingeniería Civil Informática

---

Organizador de tareas con Estructuras de datos y TDAs.
======

**Preparacion y configuracion del Repositorio**

*   Usamos la aplicación `GitHub Desktop` para crear y actualizar nuestro repositorio local, para evitar usar lo comandos `git fetch` y `git pull`, ya que estos estan integrados en la app.
*   Creamos un repositorio remoto en GitHub, el link es el siguiente: https://github.com/Matias-Guerrero/Tarea3_OrganizadorTareas
*   Utilizamos Visual Studio Code para que ambos integrantes clonaramos el repositorio en sus computadores.
*   Para subir cada commit usamos los siguiente comandos en la terminal git bash, como: `git status`, `git add .`, `git commit -m "[Message]"` y `git push`.
*   Para compilar la aplicacion se creo un script en bash llamado `compiler.sh`, el cual compila el codigo en c y crea un archivo ejecutable `.exe` con el nombre que uno ingrese.
*   Para ejecutar la aplicacion se puede hacer el llamado del ejecutable desde la terminal con el comando `./[NombreEjecutable].exe` o simplemente ejecutar el archivo `.exe` desde el administrador de archivos.

---

Estructuras de datos y TDAs implementadas
---

En esta aplicacion implementamos las siguientes estructuras de datos y TDAs: 

* Estructura de datos Arbol binario:

  ````c
  struct TreeNode {
      Pair* pair;
      TreeNode * left;
      TreeNode * right;
      TreeNode * parent;
  };

  struct TreeMap {
      TreeNode * root;
      TreeNode * current;
      int (*lower_than) (void* key1, void* key2);
  };
  ````

* TDA Mapa:

  ````c
  struct Node {
      void * key;
      /*! Puntero al dato */
      void * data;

      /*! Puntero al siguiente nodo */
      Node * next;

      /*! Puntero al anterior nodo */
      Node * prev;
  };

  struct Map {
      /*! Puntero al incio (cabeza) de la lista */
      Node * head;

      /*! Puntero al final (cola) de la lista */
      Node * tail;

      /*! Punteor para poder recorrer la lista */
      Node * current;

      int (*is_equal)(void* key1, void* key2);
      int (*lower_than)(void* key1, void* key2);

  };
  ````

* TDA Lista:

  ````c
  struct Node {
      const void * data;
      Node * next;
      Node * prev;
  };

  struct List {
      Node * head;
      Node * tail;
      Node * current;
  };
  ````

* TDA Pila:

    Se crea un archivo stack.h para renombrar las operaciones del TDA Lista y crear las operaciones de la pila:

    ````c
    typedef List Stack;

    #define stack_create() createList()

    #define stack_push(stack, data) pushFront(stack, data)

    #define stack_pop(stack) popFront(stack)

    #define stack_top(stack) firstList(stack)
    ````
---

Structs creadas
----

Se nos pidio crear una aplicación, la cual tiene por objetivo organizar las tareas por hacer. En donde el usuario ingresa el nombre de la tarea, la prioridad que tiene y establecer si tiene precedencia entre las otras tareas.

Para mantener ordenada nuestro proyecto utilizamos subcarpetas.

Para esto definimos la siguiente struct en c:

* Tarea

  ````c
  typedef struct {
    char nombreTarea[MAXCHAR];
    int prioridad;
    char tareaPrecedente[MAXCHAR];
    } Tarea;
  ````
  
* Accion

  ````c
  typedef struct {
    char nombreAccion[MAXCHAR];
    void* datoAccion;
  } Accion;
  ````

---
El programa comienza con la función main() que muestra un menú de opciones para la aplicación utilizando la estructura switch. Este menú se encuentra dentro de un bucle do-while para que el usuario pueda volver a elegir una opción después de haber completado la acción correspondiente. Si se ingresa una opción inválida, se mostrará un mensaje de error por pantalla y se volverá al menú.

Dentro de la función main(), se declaran varias variables y estructuras, incluyendo dos estructuras de datos, TreeMap y Map, que se utilizan para almacenar y organizar las tareas ingresadas por el usuario.

Funciones Implementadas
----

- **Opcion 1 :** `void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea, Stack *pilaAcciones)`.

  La opción 1 del programa se encarga de agregar una tarea al sistema. Cuando el usuario elige esta opción, se llama a la función `agregarTarea()` que toma varios argumentos, incluyendo un `TreeMap` para almacenar las tareas por orden de prioridad, un `Map` para realizar búsquedas de tareas por nombre, el nombre y la prioridad de la tarea que se va a agregar, y una `Stack` para almacenar las acciones realizadas.

  La función comienza verificando si el nombre de la tarea ya existe en el mapa de tareas utilizando la función `searchMap()`. Si la tarea no existe, se procede a crear una nueva tarea. Se reserva memoria dinámicamente para una estructura `Tarea` utilizando la función `malloc()`.

  A continuación, se asignan los valores a los campos de la tarea: se copia el nombre de la tarea en la estructura, se asigna la prioridad y se crea una lista vacía para almacenar las tareas precedentes utilizando la función `createList()`.

  Posteriormente, se inserta la tarea en el `TreeMap` utilizando la función `insertTreeMap()` con la prioridad como clave y la tarea como valor. También se inserta la tarea en el `Map` utilizando la función `insertMap()` con el nombre de la tarea como clave y la tarea como valor.

  Además, se crea una estructura `Accion` para representar la acción de agregar tarea. Se reserva memoria para la estructura y se asignan los valores correspondientes. Luego, se agrega la acción a la pila de acciones utilizando la función `stack_push()`.

  Si la tarea se agrega exitosamente, se muestra un mensaje de éxito. En caso de que la tarea ya exista, se muestra un mensaje de error.

  Finalmente, se realiza una pausa en la ejecución utilizando la función `system("pause")` para permitir al usuario leer el mensaje y luego continuar con el programa.

- **Opcion 2 :** `void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente, Stack *pilaAcciones)`.

  La opción 2 del programa permite establecer precedencia entre tareas. Cuando el usuario selecciona esta opción, se llama a la función `establecerPrecedencia()` que toma como argumentos un `TreeMap` de tareas, un `Map` de tareas, los nombres de la tarea y la tarea precedente, y una pila de acciones.

  La función comienza verificando si las tareas ingresadas son iguales utilizando la función `strcmp()`. Si las tareas son iguales, se muestra un mensaje de error indicando que no se puede establecer precedencia entre una tarea y sí misma.

  Luego, se verifica si ambas tareas existen en el mapa de tareas utilizando la función `searchMap()`. Si ambas tareas existen, se procede a realizar más verificaciones.

  Se busca la tarea actual en el mapa de tareas utilizando la función `searchMap()` y se verifica que la tarea precedente no exista en la lista de precedentes de la tarea actual. Si la tarea precedente ya existe en la lista de precedentes, se muestra un mensaje de error indicando que la precedencia ya está establecida.

  Si las verificaciones son exitosas, se crea una acción utilizando la estructura `Accion` y se agrega a la pila de acciones utilizando la función `stack_push()`. Esta acción representa el establecimiento de la precedencia entre las tareas.

  Luego, se agrega la tarea precedente a la lista de precedentes de la tarea actual utilizando la función `pushBack()`.

  Finalmente, se muestra un mensaje de éxito indicando que se ha establecido la precedencia entre las tareas.

  
- **Opcion 3 :** `void mostrarTareasPorHacer(char *nombreTarea, Map *mapaTareas, List *listaTareasPorHacer)`.

  La opción 3 del programa se encarga de mostrar las tareas por hacer, ordenadas por prioridad y precedencia. Al seleccionar esta opción, se llama a la función `mostrarTareasPorHacer()`, que toma como argumentos un árbol de tareas (`arbolTareas`) y un mapa de tareas (`mapaTareas`).

  La función comienza verificando si el árbol de tareas y el mapa de tareas no están vacíos. Si están vacíos, se muestra un mensaje de error y se pausa la ejecución del programa.

  Luego, se crea una lista llamada `listaTareasPorHacer` para almacenar las tareas por hacer. A continuación, se recorre el árbol de tareas para obtener las tareas por hacer.

  Dentro del bucle, se obtiene la tarea actual y se verifica si ya está en la lista de tareas por hacer. Si no está en la lista, se verifica si la tarea tiene tareas precedentes. Si tiene, se utilizan las funciones `guardarTareasPrecedentes()` para guardar las tareas precedentes de manera recursiva en la lista `listaTareasPorHacer`. Luego, se agrega la tarea actual a la lista de tareas por hacer utilizando la función `pushBack()`.

  Una vez obtenida la lista de tareas por hacer, se muestra en pantalla cada tarea con su prioridad. Si la tarea tiene tareas precedentes, se llama a la función `mostrarTareasPrecedentes()` para mostrarlas en orden. Finalmente, se muestra un mensaje de éxito y se pausa la ejecución del programa.

  Es importante destacar que la función `mostrarTareasPrecedentes()` se encarga de mostrar las tareas precedentes de una tarea dada. Verifica si la lista de tareas precedentes está vacía y, en caso contrario, recorre la lista para mostrar cada tarea.

  Al finalizar, se libera la memoria utilizada por la lista `listaTareasPorHacer`.
  
- **Opcion 4 :** `void marcarTareaCompletada(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, Stack *pilaAcciones)`.

  La opción 4 del programa se encarga de marcar una tarea como completada. Cuando el usuario selecciona esta opción, se llama a la función `marcarTareaCompletada()`, que toma varios argumentos, incluyendo un puntero al árbol de tareas (`arbolTareas`), un puntero al mapa de tareas (`mapaTareas`), el nombre de la tarea a marcar como completada (`nombreTarea`), y un puntero a una pila de acciones (`pilaAcciones`).

  La función comienza buscando la tarea en el mapa de tareas utilizando la función `searchMap()`. Si la tarea existe, se procede a verificar si esa tarea es precedente de alguna otra tarea. Para esto, se recorre el árbol de tareas utilizando la función `firstTreeMap()` y `nextTreeMap()` para obtener cada tarea. Si la tarea actual tiene tareas precedentes, se busca si la tarea a marcar como completada es una de esas tareas precedentes. Si se encuentra una relación de precedencia, se solicita al usuario una confirmación para eliminar la tarea. Si el usuario confirma, se crea una copia de la tarea actual y se agrega a una lista de tareas precedentes eliminadas (`listaPrecedentesEliminados`) utilizando la función `pushBack()`, y se elimina la tarea de la lista de precedentes utilizando la función `popCurrent()`.

  A continuación, se elimina la tarea del mapa de tareas utilizando la función `eraseMap()`. Luego, se recorre nuevamente el árbol de tareas para encontrar la tarea a eliminar y se utiliza la función `eraseTreeMapCurrent()` para eliminarla del árbol. Se crea una acción (`accionActual`) para agregar a la pila de acciones, que registra la eliminación de la tarea marcada como completada.

  Finalmente, se muestra un mensaje de éxito indicando que la tarea se ha completado correctamente. Si la tarea no existe, se muestra un mensaje de error correspondiente.
  
- **Opcion 5 :** `void deshacerAccion(TreeMap *arbolTareas, Map *mapaTareas, Stack *pilaAcciones)`.

  La opción 5 del programa permite deshacer la última acción realizada por el usuario. Al seleccionar esta opción, se llama a la función `deshacerAccion()` que toma tres argumentos: un árbol de tareas, un mapa de tareas y una pila de acciones.

  La función comienza obteniendo la última acción realizada desde la parte superior de la pila de acciones utilizando la función `stack_top()`. Si la pila está vacía o no hay acciones para deshacer, se muestra un mensaje de error y la función se termina.

  Luego, se verifica el tipo de la última acción utilizando `strcmp()`. Si la acción fue agregar una tarea, se procede a eliminar la tarea del mapa de tareas utilizando la función `eraseMap()` y del árbol de tareas utilizando la función `eraseTreeMapCurrent()`. Además, se muestra un mensaje de éxito indicando que la acción de agregar tarea ha sido deshecha.

  Si la última acción fue establecer precedencia entre tareas, se elimina el último elemento de la lista de tareas precedentes de la tarea correspondiente. También se muestra un mensaje de éxito indicando que la acción de establecer precedencia ha sido deshecha.

  Si la última acción fue marcar una tarea como completada, se realiza lo siguiente:

    - Se elimina la acción de la pila de acciones.
    - Se obtiene la lista de tareas precedentes eliminadas de la última acción.
    - Se agrega la tarea completada nuevamente al mapa de tareas y al árbol de tareas.
    - Se recorre la lista de tareas precedentes eliminadas y se agrega la tarea completada a la lista de tareas precedentes de cada tarea correspondiente.
    - Finalmente, se muestra un mensaje de éxito indicando que la acción de marcar tarea como completada ha sido deshecha.
    
  Al finalizar la deshacer la acción, se muestra un mensaje de éxito y se pausa la ejecución del programa antes de volver al menú principal.

- **Opcion 6 :** `void cargarTareas(TreeMap *arbolTareas, Map *mapaTareas, char *nombreArchivo)`.

  La opción 6 del programa permite cargar tareas desde un archivo. Al seleccionar esta opción, se llama a la función `cargarTareas()` que toma tres argumentos: un árbol de tareas, un mapa de tareas y el nombre del archivo que contiene las tareas.

  La función comienza abriendo el archivo de tareas utilizando la función `fopen()` en modo de lectura ("r"). Si el archivo no existe, se muestra un mensaje de error indicando que el archivo no existe y la función termina.

  Si el archivo existe, se declara una serie de variables necesarias para el procesamiento de las tareas. Luego, se lee la primera línea del archivo (se asume que es una línea de encabezado y se omite su procesamiento).

  A continuación, se inicia un bucle para leer las líneas restantes del archivo. En cada iteración, se realiza lo siguiente:

  - Se obtiene el nombre de la tarea y la prioridad utilizando la función `strtok()` para separar los campos de la línea leída.
  - Se obtiene la cadena de precedentes de la tarea utilizando `strtok()`.
  - Se crea una lista para almacenar los precedentes de la tarea utilizando la función `createList()`.
  - Si la cadena de precedentes no es nula, se separa en tokens utilizando `strtok()` y se agrega cada precedente a la lista mediante `pushBack()`.
  - Se crea una estructura `Tarea` y se asignan los valores correspondientes.
  - Se verifica si la tarea ya existe en el mapa de tareas utilizando la función `searchMap()`. Si la tarea no existe, se agrega tanto al mapa de tareas como al árbol de tareas utilizando `insertMap()` e `insertTreeMap()` respectivamente.
  
  Una vez que se han procesado todas las líneas del archivo, se muestra un mensaje de éxito indicando que las tareas se han cargado exitosamente. Luego, se cierra el archivo y se pausa la ejecución del programa antes de volver al menú principal.

  Es importante mencionar que este código asume un formato específico para el archivo de tareas, donde cada línea contiene el nombre de la tarea, la prioridad y los precedentes separados por comas. Además, los precedentes están separados por espacios.
  
- **Opcion 7 :**

  La opción 7 se encarga de salir del programa. La implementación consiste en imprimir un mensaje de despedida, esperar dos segundos y luego salir del programa.

- **Opcion 8:** `void recorrerArbolyMapa(TreeMap *arbolTareas, Map *mapaTareas)`.

  La opción 8 del programa tiene un propósito oculto y no está disponible para los usuarios regulares. Esta opción está diseñada para el desarrollo y pruebas del código y no debe ser utilizada en un entorno de producción.
  
  La función `recorrerArbolyMapa()` se utiliza para mostrar el contenido del árbol binario y el mapa de tareas.
 ---
 
 **Coevaluacion y trabajo en equipo**
 ----
 
  - **Coevaluacion Personal**

  | Nombres | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
  |--------|--------------|----------------|--------------|--------------------|------------------|-------|
  | Matias G. | 20 | 20 | 20 | 20 | 20 | 100 |
  | Fabiana P. | 20 | 20 | 20 | 20 | 20 | 100 |

  - **Coevaluacion Grupal**

  | Evaluación grupal | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
  |------------------|--------------|----------------|--------------|--------------------|------------------|-------|
  | M.G./F.P. | 20 | 20 | 20 | 20 | 20 | 100 |
 
