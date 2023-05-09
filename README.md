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
En esta aplicacion implementamos las siguientes TDAs: 

* TDA Arbol binario:

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

- **Opcion 1 :** `void agregarTarea(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, int prioridadTarea)`.

  Cuando el usuario selecciona la opción de agregar tarea en el menú, se llama a la función `agregarTarea()`, que toma cuatro argumentos: un puntero a un árbol de tareas, un puntero a un mapa de tareas, el nombre de la tarea y la prioridad de la tarea.

  La función verifica si la tarea ya existe en el mapa de tareas utilizando la función `searchMap()`. Si la tarea no existe, la función crea una nueva tarea utilizando la función `malloc` para asignar memoria dinámicamente.

  A continuación, se asignan los valores de la tarea: se copia el nombre de la tarea en la estructura `tarea->nombreTarea`, se asigna la prioridad a la estructura `tarea->prioridad` y se copia una cadena vacía en la estructura `tarea->tareaPrecedente`. La nueva tarea se agrega tanto al árbol de tareas como al mapa de tareas utilizando las funciones `insertTreeMap()` e `insertMap()`, respectivamente.

  Después, se muestra un mensaje de éxito en la pantalla utilizando la función `puts()`. Si la tarea ya existe en el mapa de tareas, se muestra un mensaje de error en su lugar.

  Por último, se utiliza la función `system("pause")` para pausar la ejecución del programa hasta que el usuario presione una tecla.

- **Opcion 2 :** `void establecerPrecedencia(TreeMap *arbolTareas, Map *mapaTareas, char *nombreTarea, char *nombreTareaPrecedente)`.

  La función `establecerPrecedencia()` se encarga de establecer una tarea precedente para una tarea existente. Recibe como argumentos un árbol de tareas (`arbolTareas`), un mapa de tareas (`mapaTareas`), el nombre de la tarea que se desea modificar (`nombreTarea`) y el nombre de la tarea precedente (`nombreTareaPrecedente`).

  Primero, la función verifica que ambas tareas existan en el mapa de tareas (`mapaTareas`) utilizando la función `searchMap()`. Si ambas tareas existen, se busca la tarea que se desea modificar en el árbol de tareas (`arbolTareas`) utilizando un ciclo while. Se obtiene el valor de cada par clave-valor del árbol de tareas hasta que se encuentra la tarea deseada.

  Una vez encontrada la tarea, se establece la tarea precedente mediante la asignación del nombre de la tarea precedente en el campo `tareaPrecedente` de la estructura `Tarea`. Posteriormente, se actualiza la tarea en el árbol de tareas utilizando la función `actualizarNodoActual()`, y en el mapa de tareas mediante la función `insertMap()`.

  Si se logra establecer la tarea precedente, se muestra un mensaje de éxito en pantalla con el nombre de la tarea y el nombre de su tarea precedente. En caso contrario, se muestra un mensaje de error indicando que la tarea o su precedente no existen.

  La función utiliza la función `system("cls")` para limpiar la pantalla y `system("pause")` para pausar la ejecución y esperar a que el usuario presione una tecla antes de continuar.