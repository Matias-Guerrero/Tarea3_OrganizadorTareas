# Tarea3_OrganizadorTareas
Tarea N°3 de Estructura de Datos, Ingeniería Civil Informática

Organizador de tareas implementado con las TDA árbol binario y lista.
======

---
**Antes de Empezar**

*   Usamos la aplicación `GitHub Desktop` para crear y actulizar nuestro repositorio local, ya que la misma aplicación realiza `git fetch` y `git pull`
*   Creamos un repositorio en GitHub, el link es el siguiente: 
*   Utilizamos Visual Studio Code para que ambos clonaramos el repositorio en sus computadores.
*   Para subir cada commit los comandos en git bash, como: `git status`, `git add .`, `git commit -m ""` y `git push`
*   Para ejecutar el codigo se creo un script `compiler.sh` y así crear un archivo `.exe`.

---
En esta aplicacion implementamos las siguientes estructuras de datos y TDAs: 

* Estructura de datos Arbol binario:

  ````c
  typedef struct TreeNode TreeNode;

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

  TreeNode * createTreeNode(void* key, void * value) {
  TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL) return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
  }
  ````

* TDA Mapa:

  ````c
  typedef struct Node Node;

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
  typedef struct Node Node;

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

  typedef List List;

  Node * createNode(const void * data) {
      Node * new = (Node *)malloc(sizeof(Node));
      assert(new != NULL);
      new->data = data;
      new->prev = NULL;
      new->next = NULL;
      return new;
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

---
El programa comienza con la función main() que muestra un menú de opciones para la aplicación utilizando la estructura switch. Este menú se encuentra dentro de un bucle do-while para que el usuario pueda volver a elegir una opción después de haber completado la acción correspondiente. Si se ingresa una opción inválida, se mostrará un mensaje de error por pantalla y se volverá al menú.

Dentro de la función main(), se declaran varias variables y estructuras, incluyendo dos estructuras de datos, TreeMap y Map, que se utilizan para almacenar y organizar las tareas ingresadas por el usuario.

Funciones Implementadas:
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
