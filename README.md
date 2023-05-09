# Tarea3_OrganizadorTareas
Tarea N°3 de Estructura de Datos, Ingeniería Civil Informática

Organizador de tareas implementado con las TDA árbol binario y lista.
======

---
**Antes de Empezar**

*   Usamos la aplicación `GitHub Desktop` para crear y actulizar nuestro repositorio local, ya que la misma aplicación realiza `git fetch` y `git pull`
*   Creamos un repositorio en GitHub, el link es el siguiente: 
*   Utilizamos Visual Studio Code para que ambos clonaramos el repositorio en sus computadores.
*   Para subir cada commit los comandos en git bash, como: `git status`, `git add .`, `git commit -m""` y `git push`
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
El programa comienza por mostrar un mensaje de bienvenida y los nombres de los desarrolladores. Luego, entra en un bucle do-while que muestra un menú de opciones al usuario y espera que el usuario seleccione una opción ingresando un valor entero. Si el valor ingresado no corresponde a una opción válida, se mostrará un mensaje de error y se volverá a mostrar el menú.

El programa comienza con la función main() que muestra un menú de opciones para la aplicación utilizando la estructura switch. Este menú se encuentra dentro de un bucle do-while para que el usuario pueda volver a elegir una opción después de haber completado la acción correspondiente. Si se ingresa una opción inválida, se mostrará un mensaje de error por pantalla y se volverá al menú.

Dentro de la función main(), se declaran varias variables y estructuras, incluyendo dos estructuras de datos, TreeMap y Map, que se utilizan para almacenar y organizar las tareas ingresadas por el usuario.

